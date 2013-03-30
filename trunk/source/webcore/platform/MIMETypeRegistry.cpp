/*
 * Copyright (C) 2006 Apple Computer, Inc.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE COMPUTER, INC. ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL APPLE COMPUTER, INC. OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "config.h"
#include "MIMETypeRegistry.h"
#include "StringHash.h"
#include <wtf/HashMap.h>
#include <wtf/HashSet.h>

namespace WebCore
{
static WTF::HashSet<String>* supportedImageResourceMIMETypes;
static WTF::HashSet<String>* supportedImageMIMETypes;
static WTF::HashSet<String>* supportedNonImageMIMETypes;
    
static void initialiseSupportedImageMIMETypes()
{    
    // assume that all implementations at least support the following standard
    static const char* types[] = {
      "image/jpeg",
      "image/jpg",
      "image/png",
      "image/gif",
      "image/bmp",
      "image/x-icon",    // ico
      "image/x-xbitmap"  // xbm
    };
    for (size_t i = 0; i < sizeof(types)/sizeof(types[0]); ++i) {
      supportedImageMIMETypes->add(types[i]);
      supportedImageResourceMIMETypes->add(types[i]);
    }
}

static void initialiseSupportedNonImageMimeTypes()
{
    static const char* types[] = {
      "text/html",
      "text/plain",
      "text/css",
      "text/javascript",
      "text/chat",
      "text/x-custom",
      "text/",
      "application/x-javascript",
      "application/javascript",
#if ENABLE(XML)
      "text/xsl",
      "text/xml",
      "text/vnd.wap.wml",
      "application/xml",
      "application/xhtml+xml",
      "application/vnd.wap.xhtml+xml",
      "application/vnd.wap.wmlc",
      "application/rss+xml",
      "application/atom+xml",
#endif      
      "multipart/x-mixed-replace",
#if ENABLE(SVG)
      "image/svg+xml",
#endif
#if ENABLE(FTPDIR)
      "application/x-ftp-directory"
#endif
    };
    for (size_t i = 0; i < sizeof(types)/sizeof(types[0]); ++i)
      supportedNonImageMIMETypes->add(types[i]);
}

static void initialiseMIMETypeRegistry()
{
    supportedImageResourceMIMETypes = new WTF::HashSet<String>();
    supportedImageMIMETypes = new WTF::HashSet<String>();
    supportedNonImageMIMETypes = new WTF::HashSet<String>();
    
    initialiseSupportedNonImageMimeTypes();
    initialiseSupportedImageMIMETypes();
}

String MIMETypeRegistry::getMIMETypeForPath(const String& path)
{
    int pos = path.reverseFind('.');
    if(pos >= 0) {
        String extension = path.substring(pos + 1);
        return getMIMETypeForExtension(extension);
    }
    return "application/octet-stream";
}

bool MIMETypeRegistry::isSupportedImageMIMEType(const String& mimeType)
{ 
    if (!supportedImageMIMETypes)
        initialiseMIMETypeRegistry();
    return !mimeType.isEmpty() && supportedImageMIMETypes->contains(mimeType); 
}

bool MIMETypeRegistry::isSupportedImageResourceMIMEType(const String& mimeType)
{ 
    if (!supportedImageResourceMIMETypes)
        initialiseMIMETypeRegistry();
    return !mimeType.isEmpty() && supportedImageResourceMIMETypes->contains(mimeType); 
}
    
bool MIMETypeRegistry::isSupportedNonImageMIMEType(const String& mimeType)
{
    if (!supportedNonImageMIMETypes)
        initialiseMIMETypeRegistry();
    return !mimeType.isEmpty() && supportedNonImageMIMETypes->contains(mimeType);
}

bool MIMETypeRegistry::isJavaAppletMIMEType(const String& mimeType)
{
    // Since this set is very limited and is likely to remain so we won't bother with the overhead
    // of using a hash set.
    // Any of the MIME types below may be followed by any number of specific versions of the JVM,
    // which is why we use startsWith()
    return mimeType.startsWith("application/x-java-applet", false) 
        || mimeType.startsWith("application/x-java-bean", false) 
        || mimeType.startsWith("application/x-java-vm", false);
}

const HashSet<String> &MIMETypeRegistry::getSupportedImageMIMETypes()
{
    if (!supportedImageMIMETypes)
        initialiseMIMETypeRegistry();
    return *supportedImageMIMETypes;
}

const HashSet<String> &MIMETypeRegistry::getSupportedImageResourceMIMETypes()
{
    if (!supportedImageResourceMIMETypes)
        initialiseMIMETypeRegistry();
    return *supportedImageResourceMIMETypes;
}

const HashSet<String> &MIMETypeRegistry::getSupportedNonImageMIMETypes()
{
    if (!supportedNonImageMIMETypes)
        initialiseMIMETypeRegistry();
    return *supportedNonImageMIMETypes;
}

}
