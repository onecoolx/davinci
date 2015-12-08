/*
 * MIMETypeRegistryDavinci.cpp: MIMETypeRegistry implements by davinci.
 *
 * Copyright(C) 2015 Zhang Ji Peng (onecoolx@gmail.com)
 *
 */


#include "config.h"
#include "MIMETypeRegistry.h"

#include "NotImplemented.h"
#include <wtf/Assertions.h>
#include <wtf/MainThread.h>

namespace WebCore {

struct ExtensionMap {
    const char* extension;
    const char* mimeType;
};

static const ExtensionMap extensionMap[] = {
    { "bmp", "image/bmp" },
    { "css", "text/css" },
    { "gif", "image/gif" },
    { "html", "text/html" },
    { "htm", "text/html" },
    { "ico", "image/x-icon" },
    { "jpeg", "image/jpeg" },
    { "jpg", "image/jpeg" },
    { "js", "application/x-javascript" },
    { "mht", "application/x-mimearchive" },
    { "mhtml", "application/x-mimearchive" },
    { "mng", "video/x-mng" },
    { "pbm", "image/x-portable-bitmap" },
    { "pgm", "image/x-portable-graymap" },
    { "pdf", "application/pdf" },
    { "png", "image/png" },
    { "ppm", "image/x-portable-pixmap" },
    { "rss", "application/rss+xml" },
    { "svg", "image/svg+xml" },
    { "text", "text/plain" },
    { "tif", "image/tiff" },
    { "tiff", "image/tiff" },
    { "txt", "text/plain" },
    { "xbm", "image/x-xbitmap" },
    { "xml", "text/xml" },
    { "xpm", "image/x-xpm" },
    { "xsl", "text/xsl" },
    { "xhtml", "application/xhtml+xml" },
    { "wml", "text/vnd.wap.wml" },
    { "wmlc", "application/vnd.wap.wmlc" },
    { 0, 0 }
};

String MIMETypeRegistry::getMIMETypeForExtension(const String &ext)
{
    ASSERT(isMainThread());

    String s = ext.lower();
    const ExtensionMap *e = extensionMap;
    while (e->extension) {
        if (s == e->extension)
            return e->mimeType;
        ++e;
    }

    return String();
}

bool MIMETypeRegistry::isApplicationPluginMIMEType(const String&)
{
    return false;
}

#if ENABLE(MEDIA_SOURCE)
bool MIMETypeRegistry::isSupportedMediaSourceMIMEType(const String&, const String&)
{
    notImplemented();
    return false;
}
#endif

}
