
#ifndef CacheManagerCurl_h
#define CacheManagerCurl_h

#include "config.h"

#if ENABLE(HTTPCACHE)
#include <wtf/PassRefPtr.h>
#include "PlatformString.h"
#include "FileSystem.h"
#include "KURL.h"
#include "Shared.h"

namespace WebCore {

struct CacheData;
class CacheManager;

class CacheItem : public Shared<CacheItem>
{
public:
	virtual ~CacheItem();
	static PassRefPtr<CacheItem> create(unsigned id, const String& lt, const String& et, const String& ct, time_t t); 

	bool isExpired() const;
	bool isValid() const;
	void incAccess(CacheManager* mgr);
	void flushData();
	void deleteData();

	bool writeData(unsigned char* data, size_t size);
	unsigned char* readData(size_t* size);
	void resetReader();

	String lastModify() { return m_lastModify; }
	String eTag() { return m_eTag; }
	String contentType() { return m_contentType; }

	unsigned id() const { return m_id; }
	void updateItem(const String& lt, const String& et, const String& ct, time_t t);
private:
	friend class CacheManager;
	friend class CacheManagerData;
	CacheItem();
	CacheItem(unsigned id, const String& lt, const String& et, const String& ct, time_t t);
	CacheItem(const struct CacheData* data);
	String getFileName() const;
	void getCoreData(CacheData* data);

	void removeFromLRU(CacheManager* mgr);
	void insertToLRU(CacheManager* mgr);

	// list member
	CacheItem *m_next;
	CacheItem *m_priv;

	unsigned m_id;
	bool m_delete;
	String m_lastModify;
	String m_eTag;
	String m_contentType;
	time_t m_startTime; // last modify time
	time_t m_ageTime;   // max age

	HFile  m_file;
	size_t  m_fileSize;
	size_t m_filePointer;
	Vector<unsigned char> m_readBuffer;
};

class CacheManagerData;

class CacheManager {
public:
	friend class CacheItem;

	static CacheManager *sharedInstance();
	static void saveAndReleaseAllCacheItems();

    void setCacheEnabled(bool enable);
    bool cacheEnabled();

	void setCacheMaxSize(size_t size);
	size_t getCacheMaxSize(void) const;
	void saveIfNeeded();
	bool freeAllItems();

	static bool setCacheDir(const String& path);
	static const String& cacheDir(void);	

	CacheItem * findCacheItem(const KURL& url);
	CacheItem * createCacheItem(const KURL& url, const String& lt, const String& et, 
															const String& ct, size_t len, time_t expt);
	void removeCacheItem(CacheItem* item);
private:
	CacheManager();
	~CacheManager();

	void checkSize(CacheItem* item, size_t len);
	void clearAll();

	String getIndexFileName() const;
	void save();
	void load();
#if USE(MULTIPLE_THREADS)
    void lock() { m_lock->lock();}
    void unlock() { m_lock->unlock();}
#else
    void lock() {}
    void unlock() {}
#endif

	CacheManagerData *m_data;
	bool m_enableCache; /* default true */
	bool m_newEntry; 
#if USE(MULTIPLE_THREADS)
    Mutex *m_lock;
#endif
	static String m_cacheDir;
};

} /* namespace WebCore */
#endif /* ENABLE(HTTPCACHE) */

#endif /* CacheManagerCurl_h */
