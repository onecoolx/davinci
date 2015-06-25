/*
 * Copyright (C) 2007 Apple Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1.  Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 * 2.  Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 * 3.  Neither the name of Apple Computer, Inc. ("Apple") nor the names of
 *     its contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE AND ITS CONTRIBUTORS "AS IS" AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL APPLE OR ITS CONTRIBUTORS BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#include "config.h"
#include <stdio.h>
#include <stdlib.h>
#if HAVE(SYS_TYPES_H)
#include <sys/types.h>
#endif
#if HAVE(SYS_STAT_H)
#include <sys/stat.h>
#endif
#if HAVE(UNISTD_H)
#include <unistd.h>
#endif

#include "FileSystem.h"

#include "CString.h"
#include "PlatformString.h"

namespace WebCore {

#if ENABLE(FILESYSTEM)
bool fileExists(const String& path)
{
    if (path.isNull() || path.isEmpty())
        return false;

    CString fsRep = fileSystemRepresentation(path);

    if (!fsRep.data() || fsRep.data()[0] == '\0')
        return false;

    struct stat fileInfo;
    // stat(...) returns 0 on successful stat'ing of the file, and non-zero in any case where the file doesn't exist or cannot be accessed
    return !stat(fsRep.data(), &fileInfo);
}

bool deleteFile(const String& path)
{
    CString fsRep = fileSystemRepresentation(path);

    if (!fsRep.data() || fsRep.data()[0] == '\0')
        return false;

    // unlink(...) returns 0 on successful deletion of the path and non-zero in any other case (including invalid permissions or non-existent file)
    return !unlink(fsRep.data());
}

bool fileSize(const String& path, long & result)
{
    CString fsRep = fileSystemRepresentation(path);

    if (!fsRep.data() || fsRep.data()[0] == '\0')
        return false;

    struct stat fileInfo;

    if (stat(fsRep.data(), &fileInfo))
        return false;

    result = fileInfo.st_size;
    return true;
}

size_t readFile(unsigned char *ptr, const String& path, size_t offset, size_t size)
{
    CString fsRep = fileSystemRepresentation(path);

    if (!fsRep.data() || fsRep.data()[0] == '\0')
        return 0;

    FILE* fp = fopen(fsRep.data(), "r");
    if (!fp)
        return 0;
    
    size_t fSize = 0;
    if (fseek(fp, offset, SEEK_SET) != 0)
        goto error;

    fSize = fread(ptr, size, 1, fp);

error:
    fclose(fp);
    return fSize;
}

String pathByAppendingComponent(const String& path, const String& component)
{
    if (path.endsWith("/"))
        return path + component;
    else
        return path + "/" + component;
}

bool makeAllDirectories(const String& path)
{
    CString fullPath = fileSystemRepresentation(path);
    if (!access(fullPath.data(), F_OK))
        return true;

    char* p = fullPath.mutableData() + 1;
    int length = fullPath.length();

    if(p[length - 1] == '/')
        p[length - 1] = '\0';
    for (; *p; ++p)
        if (*p == '/') {
            *p = '\0';
            if (access(fullPath.data(), F_OK))
                if (mkdir(fullPath.data(), S_IRWXU))
                    return false;
            *p = '/';
        }
    if (access(fullPath.data(), F_OK))
        if (mkdir(fullPath.data(), S_IRWXU))
            return false;

    return true;
}

String homeDirectoryPath()
{
	char* dir = getenv("HOME");
	String hpath(dir);
	return hpath+String("/.MaCross/");
}

CString fileSystemRepresentation(const String& path)
{
    return path.utf8();
}

HFile openFile(const String& name, const String& mode)
{
   return (HFile)fopen(name.utf8().data(), mode.utf8().data()); 
}

size_t writeFile(unsigned char *ptr, size_t size, size_t num, HFile file)
{
    return fwrite(ptr, size, num, (FILE*)file);
}

size_t readFile(unsigned char *ptr, size_t size, size_t num, HFile file)
{
    return fread(ptr, size, num, (FILE*)file);
}

long seekFile(HFile file, long offset, int where)
{
    return fseek((FILE*)file, offset, where);
}

bool closeFile(HFile file)
{
    return fclose((FILE*)file) == 0;
}

#endif

} // namespace WebCore
