/*
** MIMETypeRegistryPS.cpp: MIMETypeRegistry implements by picasso.
**
** Copyright(C) 2009 Zhang Ji Peng (onecoolx@gmail.com)
**
*/
#include "config.h"
#include "StringHash.h"
#include <wtf/HashMap.h>
#include "MIMETypeRegistry.h"
#include "CString.h"

namespace WebCore {

static WTF::HashMap<String, String> *ExtMIMETypesMap;

struct ExtensionMap {
    const char* extension;
    const char* mimeType;
};
static struct ExtensionMap g_ExtensionMap[] = {
    /* word*/
    { "xls",       "application/msexcel" },
    { "xla",       "application/msexcel" },
    { "hlp",       "application/mshelp" },
    { "chm",       "application/mshelp" },
    { "ppt",       "application/mspowerpoint" },
    { "ppz",       "application/mspowerpoint" },
    { "pps",       "application/mspowerpoint" },
    { "pot",       "application/mspowerpoint" },
    { "doc",       "application/msword" },
    { "dot",       "application/msword" },
    { "pdf",       "application/pdf" },
    { "ai",        "application/postscript" },
    { "eps",       "application/postscript" },
    { "ps",        "application/postscript" },
    { "rtf",       "application/rtf" },
    { "js",        "application/x-javascript" },
    { "swf",       "application/x-shockwave-flash" },
    /*compressed*/
    { "bz",        "application/x-bzip" },
    { "bz2",       "application/x-bzip2" },
    { "boz",       "application/x-bzip2" },
    { "gz",        "application/x-tar" },
    { "gzip",      "application/x-gzip" },
    { "tar",       "application/x-tar" },
    { "tgz",       "application/gnutar" },
    { "zip",       "application/zip" },
    { "rar",       "application/rar" },
    /*audio*/
    { "au",        "audio/basic" },
    { "snd",       "audio/basic" },
    { "mp3",       "audio/mpeg" },
    { "mid",       "audio/x-midi" },
    { "midi",      "audio/x-midi" },
    { "mp2",       "audio/x-mpeg" },
    { "wav",       "audio/x-wav" },
    /*image*/
    { "gif",       "image/gif" },
    { "jpeg",      "image/jpeg" },
    { "jpg",       "image/jpeg" },
    { "jp2",       "image/jp2"  },
    { "jpe",       "image/jpeg" },
    { "bmp",       "image/bmp" },
    { "ico",       "image/x-icon" },   
    { "png",       "image/png" },
    { "xwd",       "image/x-windowdump" },
    { "svg",       "image/svg+xml" },
    { "xbm",       "image/x-xbitmap" },
    /*html*/
    { "rss",       "application/rss+xml" },
    { "css",       "text/css" },
    { "htm",       "text/html" },
    { "html",      "text/html" },
    { "shtml",     "text/html" },
    { "xml",       "text/xml" },
    { "xsl",       "text/xsl" },
	{ "wml",	   "text/vnd.wap.wml" },
    { "xhtml",     "application/xhtml+xml" },
	{ "wmlc",	   "application/vnd.wap.wmlc" },
    /*text*/
    { "txt",       "text/chat" },
    { "txt",       "text/x-custom" },
    { "txt",       "text/plain" },
    { "text",      "text/plain" },
    /*video*/
    { "mpeg",      "video/mpeg" },
    { "mpg",       "video/mpeg" },
    { "mpe",       "video/mpeg" },
    { "rmvb",      "video/vnd.rn-realvideo" },
    { "qt",        "video/quicktime" },
    { "mov",       "video/quicktime" },
    { "viv",       "video/vnd.vivo" },
    { "vivo",      "video/vnd.vivo" },
};


static void initializeExtMIMETypeMap()
{
	ExtMIMETypesMap = new WTF::HashMap<String,String>();
	for (size_t i = 0; i < sizeof(g_ExtensionMap)/sizeof(g_ExtensionMap[0]); i++)
		ExtMIMETypesMap->add(g_ExtensionMap[i].extension, g_ExtensionMap[i].mimeType);
}

String MIMETypeRegistry::getMIMETypeForExtension(const String &ext)
{
    if (!ExtMIMETypesMap)
        initializeExtMIMETypeMap();
    if (!ext.isEmpty())
        return ExtMIMETypesMap->get(ext);
    return String();
}

Vector<String> MIMETypeRegistry::getExtensionsForMIMEType(const String& type)
{
    if (!ExtMIMETypesMap)
        initializeExtMIMETypeMap();

    Vector<String> retset;
    WTF::HashMap<String, String>::const_iterator itr = ExtMIMETypesMap->begin();
    WTF::HashMap<String, String>::const_iterator itr2 = ExtMIMETypesMap->end();
    for (; itr != itr2; ++itr) {
        if (equalIgnoringCase(itr->second , type))
            retset.append(itr->first);
    }
    return retset;
}

String MIMETypeRegistry::getPreferredExtensionForMIMEType(const String& type)
{
    if (!ExtMIMETypesMap)
        initializeExtMIMETypeMap();

    WTF::HashMap<String, String>::const_iterator itr = ExtMIMETypesMap->begin();
    WTF::HashMap<String, String>::const_iterator itr2 = ExtMIMETypesMap->end();
    for (; itr != itr2; ++itr) {
        if (equalIgnoringCase(itr->second , type))
            return itr->first;
    }
    return String();
}


bool MIMETypeRegistry::registerExtType(const String& ext, const String& mimeType)
{
	if (mimeType.isEmpty() || ext.isEmpty())
		return false;

	if (!ExtMIMETypesMap)
		initializeExtMIMETypeMap();

	if (!ExtMIMETypesMap->get(ext).isEmpty())
		return false;

	ExtMIMETypesMap->add(ext, mimeType);
	return true;
}

bool MIMETypeRegistry::unRegisterExtType(const String& extType)
{
	if (extType.isEmpty())
		return false;

	if (ExtMIMETypesMap->get(extType).isEmpty())
		return false;

	ExtMIMETypesMap->remove(extType);
	return true;
}

bool MIMETypeRegistry::isSupportedMIMEType(const String &mimeType)
{
    return isSupportedImageMIMEType(mimeType) ||
           isSupportedImageResourceMIMEType(mimeType) ||
           isSupportedNonImageMIMEType(mimeType);
}

}
