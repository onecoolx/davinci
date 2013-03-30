/*
 * Copyright (C) 2004, 2005, 2006 Apple Computer, Inc.  All rights reserved.
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

#ifndef IMAGE_SOURCE_H_
#define IMAGE_SOURCE_H_

#include <wtf/Noncopyable.h>
#include <wtf/Vector.h>

#include <picasso.h>

namespace WebCore {

class IntSize;
class SharedBuffer;

class ImageDecoder;
class ImageSource;

class ImageRef : Noncopyable
{
public: 
	ImageRef()
		: source(0)
		, index(0)
		, width(0)
		, height(0)
		, pitch(0)
		, transparent(false)
		, colorkey(false)
	{
	}

	~ImageRef()
	{
	}

	ImageSource* source;
	size_t index;
	int width;
	int height;
	int pitch;
	bool transparent;
	bool colorkey;
};


typedef ImageRef* NativeImagePtr;
typedef ImageDecoder* NativeImageSourcePtr;

const int cAnimationLoopOnce = -1;
const int cAnimationNone = -2;

class ImageSource : Noncopyable {
public:
    ImageSource();
    ~ImageSource();

    void clear();

    bool initialized() const;
    
    void setData(SharedBuffer* data, bool allDataReceived);

    bool isSizeAvailable();
    IntSize size() const;
    
    int repetitionCount();
    
    size_t frameCount() const;
    
    NativeImagePtr createFrameAtIndex(size_t);
    
    float frameDurationAtIndex(size_t);
    bool frameHasAlphaAtIndex(size_t); // Whether or not the frame actually used any alpha.
    bool frameIsCompleteAtIndex(size_t); // Whether or not the frame is completely decoded.

	//macross added
	NativeImageSourcePtr decoder(void) const { return m_decoder; }
private:
    NativeImageSourcePtr m_decoder;
};

}

#endif
