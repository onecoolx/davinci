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
#include <windows.h>

#include "FileSystem.h"

#include "CString.h"
#include "PlatformString.h"

namespace WebCore {

#if ENABLE(FILESYSTEM)

bool fileExists(const String& path)
{
    if (path.isNull() || path.isEmpty())
        return false;

    String filename = path;
    HANDLE hFile = CreateFile((LPCWSTR)filename.charactersWithNullTermination(), 0, FILE_SHARE_READ | FILE_SHARE_WRITE
        , 0, OPEN_EXISTING, FILE_FLAG_NO_BUFFERING, 0);

    CloseHandle(hFile);

    return hFile != INVALID_HANDLE_VALUE;
}

bool deleteFile(const String& path)
{
    String filename = path;
    return DeleteFile((LPCWSTR)filename.charactersWithNullTermination()) ? true : false;
}

bool fileSize(const String& path, long & result)
{
    String filename = path;
	HANDLE hFile = CreateFile((LPCWSTR)filename.charactersWithNullTermination(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (INVALID_HANDLE_VALUE==hFile) {
		return false;
	}
	
	result = GetFileSize(hFile, NULL);
	CloseHandle(hFile);
	return true;
}

String pathByAppendingComponent(const String& path, const String& component)
{
    if (component.isEmpty())
        return path;

    Vector<UChar, MAX_PATH> buffer;

    buffer.append(path.characters(), path.length());

    if (buffer.last() != L'\\' && buffer.last() != L'/'
        && component[0] != L'\\' && component[0] != L'/')
        buffer.append(L'\\');

    buffer.append(component.characters(), component.length());

    return String(buffer.data(), buffer.size());
}

bool makeAllDirectories(const String& path)
{
    int lastDivPos = max(path.reverseFind('/'), path.reverseFind('\\'));
    int endPos = path.length();
    if (lastDivPos == path.length() - 1) {
        endPos -= 1;
        lastDivPos = max(path.reverseFind('/', lastDivPos), path.reverseFind('\\', lastDivPos));
    }

    if (lastDivPos > 0) {
        if (!makeAllDirectories(path.substring(0, lastDivPos)))
            return false;
    }

    String folder(path.substring(0, endPos));
    CreateDirectory((LPCWSTR)folder.charactersWithNullTermination(), 0);

    DWORD fileAttr = GetFileAttributes((LPCWSTR)folder.charactersWithNullTermination());
    return fileAttr != 0xFFFFFFFF && (fileAttr & FILE_ATTRIBUTE_DIRECTORY);
}

String homeDirectoryPath()
{
	UChar path[MAX_PATH] = {0};
	GetModuleFileName(0, (LPWSTR)path, MAX_PATH);
	String hpath(path);

	hpath = hpath.left(hpath.reverseFind('\\'));
	return hpath+String("\\");
}

CString fileSystemRepresentation(const String&)
{
    return "";
}

size_t readFile(unsigned char *ptr, const String& path, size_t offset, size_t size)
{
	if (path.isNull() || path.isEmpty())
		return 0;

    String filename = path;
    FILE* fp = _wfopen((LPCWSTR)filename.charactersWithNullTermination(), L"rb");
    if (!fp)
        return 0;
    
    size_t fSize = 0;
    if (fseek(fp, offset, SEEK_SET) != 0)
        goto error;

    fSize = fread(ptr, 1, size, fp);

error:
    fclose(fp);
    return fSize;
}

HFile openFile(const String& name, const String& mode)
{
   String fname = name;
   String fmode = mode;
   return (HFile)_wfopen((LPCWSTR)fname.charactersWithNullTermination(),(LPCWSTR)fmode.charactersWithNullTermination()); 
}

long seekFile(HFile file, long offset, int where)
{
    return fseek((FILE*)file, offset, where);
}

size_t writeFile(unsigned char *ptr, size_t size, size_t num, HFile file)
{
    return fwrite(ptr, size, num, (FILE*)file);
}

size_t readFile(unsigned char *ptr, size_t size, size_t num, HFile file)
{
    return fread(ptr, size, num, (FILE*)file);
}

bool closeFile(HFile file)
{
    return fclose((FILE*)file) == 0;
}
#endif
} // namespace WebCore

