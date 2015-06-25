
#include "config.h"

#if ENABLE(HTTPCACHE)

#if !ENABLE(FILESYSTEM)
#error "Please support file system."
#endif
#include <time.h>
#include <wtf/HashMap.h>
#include "CString.h"
#include "CacheManagerCurl.h"

namespace WebCore { 

//default cache 16MB
#define DEFAULT_CACHE_SIZE	(1024*1024*16)
//default read buffer 32KB
#define DEFAULT_READ_SIZE (1024*128) 
//default string buffer 64 byte
#define STR_FIELD_SIZE (64)

static const char cMagic[] = "MCCF";

struct CacheIndexFileHeader {
	char m_magic[4];
	long m_numCacheFiles;
};

struct CacheData {
	unsigned id;
	char last[STR_FIELD_SIZE];
	char etag[STR_FIELD_SIZE];
	char content[STR_FIELD_SIZE];
	unsigned stime;
	unsigned age;
	unsigned size;
};

typedef WTF::HashMap<unsigned, RefPtr<CacheItem> > CacheMap;

class CacheManagerData
{
public:
	CacheManagerData() 
		: cache_size(0)
		, cache_size_max(DEFAULT_CACHE_SIZE)
   	{
	}

	~CacheManagerData()
   	{
	}

	CacheMap entrys;
	CacheItem lru_head;
	size_t cache_size;
	size_t cache_size_max;
};

// CacheItem
PassRefPtr<CacheItem> CacheItem::create(unsigned id, const String& lt, const String& et, const String& ct, time_t t)
{
	return PassRefPtr<CacheItem>(new CacheItem(id, lt, et, ct, t));
}

CacheItem::CacheItem()
	: m_next(0)
	, m_priv(0)
	, m_id(0)
	, m_delete(false)
	, m_startTime(0)
	, m_ageTime(0)
	, m_file(INVALID_FILE_HANDLE)
	, m_fileSize(0)
	, m_filePointer(0)
{
	//Note: only use for LRU list head.
	//This approach comes from the linux kernel
	m_next = this;
	m_priv = this;
}

CacheItem::CacheItem(unsigned id, const String& lt, const String& et, const String& ct, time_t t)
	: m_next(0)
	, m_priv(0)
	, m_id(id)
	, m_delete(false)
	, m_lastModify(lt)
	, m_eTag(et)
	, m_contentType(ct)
	, m_startTime(time(0))
	, m_ageTime(t)
	, m_file(INVALID_FILE_HANDLE)
	, m_fileSize(0)
	, m_filePointer(0)
{

	String path = getFileName();
	if (fileExists(path)) {
		deleteFile(path);
	}
}

CacheItem::CacheItem(const struct CacheData* data)
	: m_next(0)
	, m_priv(0)
	, m_delete(false)
	, m_file(INVALID_FILE_HANDLE)
	, m_filePointer(0)
{
	m_id = (unsigned)(data->id);
	m_lastModify = String(data->last);
	m_eTag = String(data->etag);
	m_contentType = String(data->content);
	m_startTime = (time_t)(data->stime);
	m_ageTime = (time_t)(data->age);
	m_fileSize = (size_t)(data->size);
}

CacheItem::~CacheItem()
{
	if (m_next) 
		m_next->m_priv = m_priv;

	if (m_priv) 
		m_priv->m_next = m_next;
	
	m_next = m_priv = 0;

	flushData();

	if (m_delete) {
		String path = getFileName();
		deleteFile(path);
		m_fileSize = 0;
	}
}

void CacheItem::removeFromLRU(CacheManager* mgr)
{
	if (m_next) 
		m_next->m_priv = m_priv;
	
	if (m_priv) 
		m_priv->m_next = m_next;
	
	m_next = m_priv = 0;

	if (mgr)
		mgr->m_data->cache_size -= m_fileSize;
}

void CacheItem::insertToLRU(CacheManager* mgr)
{
	if (mgr) {
		CacheItem * head = &(mgr->m_data->lru_head);

		m_next = head->m_next;
		head->m_next->m_priv = this;
		m_priv = head;
		head->m_next = this;

		mgr->m_data->cache_size += m_fileSize;
	}
}

void CacheItem::getCoreData(CacheData* data)
{
	if (data) {
		data->id = m_id;
		memset(data->last, 0, STR_FIELD_SIZE);
		strncpy(data->last, m_lastModify.latin1().data(), STR_FIELD_SIZE-1);
		memset(data->etag, 0, STR_FIELD_SIZE);
		strncpy(data->etag, m_eTag.latin1().data(), STR_FIELD_SIZE-1); 
		memset(data->content, 0, STR_FIELD_SIZE);
		strncpy(data->content, m_contentType.latin1().data(), STR_FIELD_SIZE-1); 
		data->stime = (unsigned)m_startTime;
		data->age = (unsigned)m_ageTime;
		data->size = (unsigned)m_fileSize;
	}
}

void CacheItem::updateItem(const String& lt, const String& et, const String& ct, time_t t)
{
	m_lastModify = lt;
	m_eTag = et;
	m_contentType = ct;
	m_startTime = time(0);
	m_ageTime = t;
	m_fileSize = 0;
	m_filePointer = 0;

	flushData();

	String path = getFileName();
	deleteFile(path);

	m_file = openFile(path, "a+"); 
}

String CacheItem::getFileName() const
{
	String name = CacheManager::cacheDir() + "/";
	name += String::number(m_id)+String(".dat");
	return name;
}

void CacheItem::incAccess(CacheManager* mgr)
{
	flushData();

	if (mgr) {
		removeFromLRU(mgr);
		insertToLRU(mgr);
	}

	String path = getFileName();
	m_file = openFile(path, "a+b"); 
}

void CacheItem::deleteData()
{
	m_delete = true;
}

void CacheItem::flushData()
{
	if (m_readBuffer.size())
		m_readBuffer.clear();

	if (m_file != INVALID_FILE_HANDLE) {
		closeFile(m_file);
		m_file = INVALID_FILE_HANDLE;
	}
}

void CacheItem::resetReader()
{
	m_filePointer = 0;
	m_readBuffer.resize((m_fileSize < DEFAULT_READ_SIZE) ? m_fileSize : DEFAULT_READ_SIZE);
}

unsigned char* CacheItem::readData(size_t* size)
{
	if (m_file != INVALID_FILE_HANDLE) {
		if (seekFile(m_file, m_filePointer, SEEK_SET) == 0) {
			m_readBuffer.fill(0);
			size_t rs = readFile(m_readBuffer.data(), 1, m_readBuffer.size(), m_file);
			if (size) *size = rs;
			m_filePointer += rs;
			return m_readBuffer.data();
		} else {
			return 0;
		}
	}
	return 0;
}

bool CacheItem::writeData(unsigned char* data, size_t size)
{
	if (m_file != INVALID_FILE_HANDLE) {
		size_t write_size = 0;
		if ((int)(write_size = writeFile(data, 1, size, m_file)) > 0) {	
			m_fileSize += write_size;
			return true;
		}
	}
	return false;
}

bool CacheItem::isValid() const
{
	String path = getFileName();
	long size = 0;
	if (fileSize(path, size)) {
		if ((size_t)size == m_fileSize)
			return true;
	}
	return false;
}

bool CacheItem::isExpired() const
{
	//FIXME: it is not more than 2038 year!! : )
	return time(0) > (m_startTime+m_ageTime);
}

//CacheManager
CacheManager *CacheManager::sharedInstance()
{
	static CacheManager * sharedCacheManager = NULL;
	if (!sharedCacheManager) {
		sharedCacheManager = new CacheManager();
		sharedCacheManager->load();
	}
	return sharedCacheManager;
}

void CacheManager::saveAndReleaseAllCacheItems()
{
	CacheManager::sharedInstance()->save();
	CacheManager::sharedInstance()->clearAll();
}

void CacheManager::checkSize(CacheItem* item, size_t len)
{
	while ((m_data->cache_size + len) > m_data->cache_size_max) {
		CacheItem* tail = m_data->lru_head.m_priv;
		if (tail != &(m_data->lru_head))
			removeCacheItem(tail);
		else
			break;
	}

	m_data->cache_size += len;
}

void CacheManager::removeCacheItem(CacheItem* item)
{
	// remove bad cache item
	lock();
	item->deleteData();
	item->removeFromLRU(this);
	m_data->entrys.remove(item->id());
	unlock();
}

CacheItem * CacheManager::findCacheItem(const KURL& url)
{
	lock();
	RefPtr<CacheItem> item = m_data->entrys.get(url.urlHash());
	unlock();
	return item.get();
}

CacheItem * CacheManager::createCacheItem(const KURL& url, const String& lt, 
											const String& et, const String& ct, size_t len, time_t expt)
{
	RefPtr<CacheItem> item = CacheItem::create(url.urlHash(), lt, et, ct, expt);
	lock();
	checkSize(item.get(), len);
	m_data->entrys.set(url.urlHash(), item);
	item->insertToLRU(this);
	m_newEntry = true;
	unlock();
	return item.get();
}

String CacheManager::m_cacheDir = String();

CacheManager::CacheManager()
	: m_data(new CacheManagerData)
	, m_enableCache(true)
	, m_newEntry(false)
{
#if USE(MULTIPLE_THREADS)
    m_lock = new Mutex;
#endif
}

CacheManager::~CacheManager()
{
	delete m_data;
#if USE(MULTIPLE_THREADS)
    delete m_lock;
#endif
}

bool CacheManager::freeAllItems()
{
	lock();
	for (CacheItem* it = m_data->lru_head.m_priv; it != &(m_data->lru_head); it = it->m_priv) {
		it->deleteData();
	}
	unlock();

	clearAll();
	save();
	return true;
}

void CacheManager::saveIfNeeded()
{
	if (m_newEntry){
		save();
		m_newEntry = false;
	}
}

size_t CacheManager::getCacheMaxSize(void) const
{
	return m_data->cache_size_max;
}

void CacheManager::setCacheMaxSize(size_t size)
{
	m_data->cache_size_max = size;
}

void CacheManager::setCacheEnabled(bool enable)
{
	m_enableCache = enable;
}

bool CacheManager::cacheEnabled()
{
	return m_enableCache;
}

const String& CacheManager::cacheDir(void)
{
	if (CacheManager::m_cacheDir.isEmpty()) {
		setCacheDir(homeDirectoryPath() + String("caches"));
	}
	return CacheManager::m_cacheDir;
}

bool CacheManager::setCacheDir(const String& path)
{
    if (!path.isEmpty() && makeAllDirectories(path)) {
        CacheManager::m_cacheDir = path;
        return true;
    }
    return false;
}

String CacheManager::getIndexFileName() const
{
	String name = CacheManager::cacheDir() + "/";
	name += String("index.dat");
	return name;
}

void CacheManager::load()
{
	String fileName = getIndexFileName();

    HFile fp = openFile(fileName, "r+b");
    if (fp == INVALID_FILE_HANDLE)
    	return;

	unsigned count = 0;
	CacheIndexFileHeader header;

	if (!readFile((unsigned char*)&header, sizeof(CacheIndexFileHeader), 1, fp))
		return;

	count = header.m_numCacheFiles;

	lock();

	for (unsigned i = 0; i < count; i++) {
		CacheData data = {0};
		if (!readFile((unsigned char*)&data, sizeof(CacheData), 1, fp))
			break;

		RefPtr<CacheItem> item = new CacheItem(&data);	
		if (item->isValid() && !item->isExpired()) {
			item->insertToLRU(this);
			m_data->entrys.set(item->id(), item);
		} else {
			item->deleteData();
		}
	}
	unlock();

    closeFile(fp);
}

void CacheManager::clearAll()
{
	lock();
	m_data->entrys.clear();
	unlock();
}

void CacheManager::save()
{
	String fileName = getIndexFileName();

    HFile fp = openFile(fileName, "w+b");
    if (fp == INVALID_FILE_HANDLE)
    	return;

	lock();
	unsigned count = m_data->entrys.size();

	CacheIndexFileHeader header;

	memcpy(&header.m_magic, cMagic, sizeof(cMagic)-1);
	header.m_numCacheFiles = count;

	writeFile((unsigned char*)&header, sizeof(CacheIndexFileHeader), 1, fp);

	for (CacheItem* it = m_data->lru_head.m_priv; it != &(m_data->lru_head); it = it->m_priv) {
		CacheData data = {0};
		it->getCoreData(&data);
		writeFile((unsigned char*)&data, sizeof(CacheData), 1, fp);
	}
	unlock();

    closeFile(fp);
}

}/*namespace WebCore*/
#endif /* ENABLE(HTTPCACHE) */

