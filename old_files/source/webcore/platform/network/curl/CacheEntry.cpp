
#include "config.h"
#include <wtf/PassRefPtr.h>
#include "CacheEntry.h"
#include "CacheManager.h"

#if ENABLE(HTTPCACHE)
namespace WebCore {

CacheEntry CacheEntry::queryEntry(const KURL& url)
{
	if (url.isValid()) {
		CacheItem* item = CacheManager::sharedInstance()->findCacheItem(url);
		if (!item)
			return CacheEntry();

		if (item->isExpired() || !item->isValid()) {
			CacheManager::sharedInstance()->removeCacheItem(item);
			return CacheEntry();
		} else {
			item->incAccess(CacheManager::sharedInstance());
			return CacheEntry(item);
		}
	}
	return CacheEntry();
}

CacheEntry CacheEntry::createEntry(const KURL& url, const String& lt, const String& et, 
																		const String& ct, size_t l, time_t expt)
{
	if (url.isValid()) {
		CacheItem * item = CacheManager::sharedInstance()->createCacheItem(url, lt, et, ct, l, expt);
		if (!item)
			return CacheEntry();
		item->incAccess(CacheManager::sharedInstance());
		return CacheEntry(item);
	}
	return CacheEntry();
}

void CacheEntry::updateEntry(CacheEntry& entry, const String& lt, const String& et, const String& ct, time_t expt)
{
	CacheItem* item = entry.m_impl.get();
	if (item) {
		item->updateItem(lt, et, ct, expt);
	}
}


CacheEntry::CacheEntry()
	: m_impl(0)
{
}

CacheEntry::CacheEntry(CacheItem* item)
	: m_impl(item)
{
}

CacheEntry::~CacheEntry()
{
}

void CacheEntry::clear(void)
{
	if (m_impl)
		m_impl->flushData();
	m_impl.release();
}

bool CacheEntry::isValid(void)
{
	return m_impl;
}

bool CacheEntry::isExpired(void)
{
	if (m_impl)
		return m_impl->isExpired();		
	else 
		return false;
}

String CacheEntry::getLastModify(void)
{
	if (m_impl)
		return m_impl->lastModify();
	else
		return String();
}

String CacheEntry::getContentType(void)
{
	if (m_impl)
		return m_impl->contentType();
	else
		return String();
}

String CacheEntry::getETag(void)
{
	if (m_impl)
		return m_impl->eTag();
	else
		return String();
}

bool CacheEntry::putData(unsigned char* data, size_t size)
{
	if (m_impl)
		return m_impl->writeData(data, size);
	return false;
}

void CacheEntry::resetReader(void)
{
	if (m_impl)
		m_impl->resetReader();
}

unsigned char* CacheEntry::getData(size_t * size)
{
	if (m_impl)
		return m_impl->readData(size);
	else
		return 0;
}

} /* namespace WebCore */
#endif /* ENABLE(HTTPCACHE) */
