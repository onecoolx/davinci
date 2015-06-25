#include <stdio.h>
#include "config.h"

#if ENABLE(FILECOOKIE)

#if !ENABLE(FILESYSTEM)
#error "Please support file system."
#endif

#include <Vector.h>
#include "CookieManager.h"
#include "PlatformString.h"
#include "CookieArchiver.h"
#include "FileSystem.h"
#include <wtf/StringExtras.h>

namespace WebCore{ 

class CookieManager;

static const char cMagic[] = "MCKF";

struct CookieFileHeader{
    char m_magic[4];
    long m_numOfCookies;
};

struct CookieItem{
    long m_size;
    long m_next;
    time_t m_expiry;
    short m_nameLen;
    short m_valueLen;
    short m_hostLen;
    short m_pathLen;
    char  m_version;
    char  m_isSecure;
    char  m_isDomain;
    char  m_isHttpOnly;
};

struct CookieEntry {
    CookieItem item;
    char  *m_name;
    char  *m_value;
    char  *m_host;
    char  *m_path;
};

struct DomainFileHeader {
    char m_magic[4];
    long m_numOfDomains;
    long m_numOfCookies;
};

#define SEEK_FILE(offset, where) seekFile(fp, offset, where)

#define WRITE_FIELD(ptr, len) writeFile((unsigned char*)ptr, len, 1, fp)

#define READ_FIELD_FAILED_GOTO(ptr, len, Label) \
    do { \
        if (!readFile((unsigned char*)ptr, len, 1, fp)) \
            goto Label; \
    }while(0)

#define READ_FIELD_RETURN_VALUE(ptr, len, ret) \
do { \
    ret = readFile((unsigned char*)ptr, len, 1, fp); \
    if (!ret) \
       ret = -1; \
}while(0)

#define READ_ITEM_FROM_UTF8STRING(item, buf, len) \
do { \
    if (len) { \
        item = String::fromUTF8(buf, len); \
        buf += len; \
    } \
}while(0)

CookieArchiver::CookieArchiver()
{
	setCookieDir(homeDirectoryPath() + String("cookies"));
}

CookieArchiver::~CookieArchiver()
{
}

int CookieArchiver::save(DomainCookie *domain)
{
    if (!domain && m_cookieDir.isEmpty())
        return -1;

	String fileName = m_cookieDir + "/";
	fileName += domain->domain();
	fileName += ".dat";

    HFile fp = openFile(fileName, "w+");
    if (!fp)
         return -1;

    CookieFileHeader fileHeader;
    fileHeader.m_numOfCookies = domain->cookieCount();
    memcpy(fileHeader.m_magic, cMagic, sizeof(fileHeader.m_magic));
    WRITE_FIELD(&fileHeader, sizeof(fileHeader));

    int num = 0;
    Cookie *cNext = domain->m_head;
    while (cNext) {
        if (serialize(cNext, fp))
            num++;
        cNext = cNext->m_next; 
    }

    if (num && (num != domain->cookieCount())) {
        SEEK_FILE(0, SEEK_SET); 
        fileHeader.m_numOfCookies = num;
        WRITE_FIELD(&fileHeader, sizeof(fileHeader));
    }
    
    closeFile(fp);
    
    if (!num)
        deleteFile(fileName);
    return num;
}

bool CookieArchiver::serialize(Cookie *cookie, HFile fp)
{
    if (cookie->isExpired() || cookie->m_expiry == 0)
        return false;

    CookieEntry entry;
    CookieItem *item = &entry.item;

    memset(&entry, 0, sizeof(entry));
    entry.m_name = (char*)fastStrdup(cookie->m_name.utf8().data());
    item->m_nameLen = cookie->m_name.utf8().length();
    entry.m_value = (char*)fastStrdup(cookie->m_value.utf8().data());
    item->m_valueLen = cookie->m_value.utf8().length();
    entry.m_host = (char*)fastStrdup(cookie->m_host.utf8().data());
    item->m_hostLen = cookie->m_host.utf8().length();
    entry.m_path = (char*)fastStrdup(cookie->m_path.utf8().data());
    item->m_pathLen = cookie->m_path.utf8().length();
  
    item->m_expiry = cookie->m_expiry;
    item->m_isDomain = cookie->m_isDomain;
    item->m_isSecure = cookie->m_isSecure;
    item->m_isHttpOnly = cookie->m_isHttpOnly;

    WRITE_FIELD(item, sizeof(*item));
    WRITE_FIELD(entry.m_name, item->m_nameLen);
    WRITE_FIELD(entry.m_value, item->m_valueLen);
    WRITE_FIELD(entry.m_host, item->m_hostLen);
    WRITE_FIELD(entry.m_path, item->m_pathLen);

    fastFree(entry.m_name);
    fastFree(entry.m_value);
    fastFree(entry.m_host);
    fastFree(entry.m_path);
    return true;
}

int CookieArchiver::loadDomain(DomainCookie *domain)
{
    int ret = 0;
 
	String fileName = m_cookieDir + "/";
	fileName += domain->domain();
	fileName += ".dat";

    HFile fp = openFile(fileName, "r+");
    if (!fp)
         return -1;

    /* read the header of the cookie file*/
    CookieFileHeader fileHeader;
    READ_FIELD_FAILED_GOTO(&fileHeader, sizeof(fileHeader), EXIT);

    for (long i=0; i<fileHeader.m_numOfCookies; i++) {
        CookieItem item;

        READ_FIELD_RETURN_VALUE(&item, sizeof(item), ret);
        if (-1 == ret)
            continue;

        size_t size = item.m_nameLen + item.m_valueLen + item.m_hostLen + item.m_pathLen;
        char *pBuf = new char[size];
        Cookie *cookie = new Cookie;

        READ_FIELD_RETURN_VALUE(pBuf, size, ret);
        if (-1 != ret) {
            char *pData = pBuf;
            READ_ITEM_FROM_UTF8STRING(cookie->m_name, pData, item.m_nameLen);
            READ_ITEM_FROM_UTF8STRING(cookie->m_value, pData, item.m_valueLen);
            READ_ITEM_FROM_UTF8STRING(cookie->m_host, pData, item.m_hostLen);
            READ_ITEM_FROM_UTF8STRING(cookie->m_path, pData, item.m_pathLen);

            cookie->m_expiry = item.m_expiry;
            cookie->m_isSecure = (item.m_isSecure == 1);
            cookie->m_isHttpOnly = (item.m_isHttpOnly == 1);
            cookie->m_isDomain = (item.m_isDomain == 1);

            if (!cookie->isExpired())
                domain->add(cookie);
        }
        delete[] pBuf;
    }

EXIT:
    closeFile(fp);
    return domain->cookieCount();
}

int CookieArchiver::load(CookieManager *mgr)
{
    if (!mgr && m_cookieDir.isEmpty())
        return -1;

	String fileName = m_cookieDir + "/index.dat";
    HFile fp = openFile(fileName, "r+");
    if (!fp)
         return -1; 

    /* read the header and check well format */
    int numOfCookies = 0;
    DomainFileHeader domainHeader;
    READ_FIELD_FAILED_GOTO(&domainHeader, sizeof(domainHeader), EXIT);
    
    for (int i=0; i<domainHeader.m_numOfDomains; i++) {
        int num;
        int ret = 0;
        size_t domainLen = 0;
        READ_FIELD_RETURN_VALUE(&domainLen, sizeof(domainLen), ret);
        if (-1 == ret)
            continue;

        /* new DomainCookie */
        ASSERT(domainLen);
        
        char *pBuf = new char[domainLen];
        READ_FIELD_RETURN_VALUE(pBuf, domainLen, ret);
        if (-1 != ret) {
            DomainCookie *domain = new DomainCookie(String::fromUTF8(pBuf, domainLen));
            if ((num = loadDomain(domain)) >= 0) {
                mgr->addDomain(domain);
                numOfCookies += num;
            } else 
                delete domain;
        }
        delete[] pBuf;
    }

EXIT:
    closeFile(fp);
    return mgr->setCookieCount(numOfCookies);
}

bool CookieArchiver::save(CookieManager *mgr)
{
    if (!mgr && m_cookieDir.isEmpty())
        return false;

	String fileName = m_cookieDir + "/index.dat";
    HFile fp = openFile(fileName, "w+");
    if (!fp)
         return false;
 
    Vector<DomainCookie*> &domains = mgr->domains();
    size_t size = domains.size(); 
    DomainFileHeader domainHeader;

    domainHeader.m_numOfCookies = mgr->cookieCount();
    domainHeader.m_numOfDomains = size;

    memcpy(&domainHeader.m_magic, cMagic, sizeof(cMagic)-1);
    WRITE_FIELD(&domainHeader, sizeof(domainHeader));

    for (size_t i=0; i<size; i++) {
        size_t length = domains[i]->domain().utf8().length();
        WRITE_FIELD(&length, sizeof(length));
        WRITE_FIELD(domains[i]->domain().utf8().data(), length);
    }

    closeFile(fp);
    return true;
}

void CookieArchiver::deleteDomain(DomainCookie* domain)
{
	String fileName = m_cookieDir + "/";
	fileName += domain->domain();
	fileName += ".dat";
    deleteFile(fileName);
}

bool CookieArchiver::setCookieDir(const String& path)
{
    if (!path.isEmpty() && makeAllDirectories(path)) {
        m_cookieDir = path;
        return true;
    }
    return false;
}

} /* namespace WebCore */

#endif
