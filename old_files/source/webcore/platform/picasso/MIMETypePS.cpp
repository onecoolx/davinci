/*
** MIMEType.cpp: identify mimeType.
**
** Copyright(C) 2009 Zhang Ji Peng (onecoolx@gmail.com)
**
*/

#include "config.h"

#include "wtf/ASCIICType.h"
#include "MIMETypePS.h"
#include "MIMETypeRegistry.h"
#include <wtf/StringExtras.h>

namespace WebCore {

MIMEType::MIMEType(const String &mimeType)
    : m_mimeType(mimeType)
{
    if (mimeType.isEmpty())
        m_category = unknown;
    else if (mimeType.startsWith("text/", false))
        m_category = text;
    else if (mimeType.startsWith("image/", false)) {
        if (mimeType.contains("svg"))
            m_category = text;
        else
            m_category = image;
    }
    else if (mimeType.startsWith("application/", false)) {
        if (mimeType.contains("application/octet-stream", false))
            m_category = unknown;
        else if (mimeType.contains("application/x-ftp-directory", false))
            m_category = text;
        else if (mimeType.contains("application/xhtml+xml", false))
            m_category = text;
        else if (mimeType.contains("application/xml", false))
            m_category = text;
        else
            m_category = application;
    }
    else if (mimeType.startsWith("audio/", false))
        m_category = audio;
    else if (mimeType.startsWith("video/", false))
        m_category = video;
    else 
        m_category = unknown;
}

MIMEType MIMEType::guestFromResource(const KURL &url, const void *ptr, size_t size)
{
    static const char *mimeTypes[] = {
        "application/octet-stream",
        "text/html", "text/plain",
        "image/gif", "image/png", "image/jpeg", "image/bmp"
    };

    size_t i;
    int typeIdx = 0;
    const char *p = static_cast<const char*>(ptr);

    for (i = 0; i < size && WTF::isASCIISpace(p[i]); ++i);

    if ((size - i >= 5  && !strncasecmp(p+i, "<html", 5))
       || (size - i >= 5  && !strncasecmp(p+i, "<head", 5))
       || (size - i >= 6  && !strncasecmp(p+i, "<title", 6))
       || (size - i >= 14 && !strncasecmp(p+i, "<!doctype html", 14))
       || (size - i >= 17 && !strncasecmp(p+i, "<!-- HTML listing", 17))) {
        /* HTML */
        typeIdx = 1;
    } else if (size >= 4 && !strncasecmp(p, "GIF8", 4)) {
        /* Images */
        typeIdx = 3;
    } else if (size >= 4 && !strncasecmp(p, "\x89PNG", 4)) {
        typeIdx = 4;
    } else if (size >= 2 && !strncasecmp(p, "\xff\xd8", 2)) {
        /* JPEG has the first 2 bytes set to 0xffd8 in BigEndian - looking
         * at the character representation should be machine independent. */
        typeIdx = 5;
    } else if (size >= 2 && !strncasecmp(p, "BM", 2)) {
        typeIdx = 6;
    } else {
        /* Text */
        /* We'll assume ASCII if chars are below 128 (after all, this
         * is a last resort when the server doesn't send Content-Type) */
        size = (size<256)?  size: 256;
        for (i=0; i<size; i++) {
            if (!isascii(p[i]))
                break;
        }
        typeIdx = (i<size) ? 0 : 2;
    }

    String mime = MIMETypeRegistry::getMIMETypeForPath(String(url.url()));
    MIMEType mimeFromUrl(mime);
    if (typeIdx == 0)
        return MIMEType("application/octet-stream");

    if (typeIdx == 2 && mimeFromUrl.isText())
        return mimeFromUrl;

    return MIMEType(mimeTypes[typeIdx]);
}

} /* namespace WebCore */

