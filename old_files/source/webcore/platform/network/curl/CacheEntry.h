
#ifndef CacheEntry_h
#define CacheEntry_h

#if ENABLE(HTTPCACHE)
#include <time.h>
#include <wtf/RefPtr.h>
#include "PlatformString.h"
#include "KURL.h"

namespace WebCore {
class CacheItem;

class CacheEntry {
public:
	static CacheEntry queryEntry(const KURL& url);
	static CacheEntry createEntry(const KURL& url, const String& lt, const String& et,
		   														const String& ct, size_t len, time_t expt);
	static void updateEntry(CacheEntry& entry, const String& lt, const String& et, const String& ct, time_t expt);
public:
	CacheEntry();
	CacheEntry(CacheItem*);	
	~CacheEntry();

	void clear(void);
	bool isValid(void);
	bool isExpired(void);

	bool putData(unsigned char* data, size_t size);
	void resetReader(void);
	unsigned char* getData(size_t * size);

	String getLastModify(void);
	String getETag(void);
	String getContentType(void);
private:
	RefPtr<CacheItem> m_impl;
};

} /* namespace WebCore */

#endif /* ENABLE(HTTPCACHE) */
#endif /*CacheEntry_h*/
