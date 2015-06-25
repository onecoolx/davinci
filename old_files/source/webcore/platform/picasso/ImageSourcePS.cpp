/*
** ImageSourcePS.cpp: ImageSource implements by picasso.
**
** Copyright(C) 2009 Zhang Ji Peng (onecoolx@gmail.com)
**
*/

#include "stdlib.h"
#include "config.h"

#include "ImageDecoder.h"
#include "ImageSource.h"
#include "SharedBuffer.h"
#include "Debug.h"

#ifdef GIF_SUPPORT
#include "GIFImageDecoder.h"
#endif /* GIF_SUPPORT */

#ifdef JPEG_SUPPORT
#include "JPEGImageDecoder.h"
#endif /* JPEG_SUPPORT */

#ifdef PNG_SUPPORT
#include "PNGImageDecoder.h"
#endif /* PNG_SUPPORT */

#ifdef BMP_SUPPORT
#include "BMPImageDecoder.h"
#endif /* BMP_SUPPORT */

#ifdef ICO_SUPPORT
#include "ICOImageDecoder.h"
#endif /* ICO_SUPPORT */

#ifdef XBM_SUPPORT
#include "XBMImageDecoder.h"
#endif /* XBM_SUPPORT */

namespace WebCore {

extern ps_color_format pixelFormat(void);
extern int pixelPerBytes(void);

ImageDecoder* createDecoder(const Vector<char>& data)
{
    // We need at least 4 bytes to figure out what kind of image we're dealing with.
    int length = data.size();
    if (length < 4)
        return 0;
    
    const unsigned char* uContents = (const unsigned char*) data.data();
    const char* contents = data.data();

#ifdef GIF_SUPPORT
    // GIFs begin with GIF8(7 or 9).
    if (strncmp(contents, "GIF8", 4) == 0)
    {
        return new GIFImageDecoder();
    }
#endif /* GIF_SUPPORT */

#ifdef PNG_SUPPORT
    // Test for PNG.
    if (uContents[0] == 0x89 &&
        uContents[1] == 0x50 &&
        uContents[2] == 0x4E &&
        uContents[3] == 0x47)
    {
        return new PNGImageDecoder();
    }
#endif /* PNG_SUPPORT */

#ifdef JPEG_SUPPORT
    // JPEG
    if (uContents[0] == 0xFF &&
        uContents[1] == 0xD8 &&
        uContents[2] == 0xFF)
    {
        return new JPEGImageDecoder();
    }
#endif /* JPEG_SUPPORT */

#ifdef BMP_SUPPORT
    // BMP
    if (strncmp(contents, "BM", 2) == 0)
    {
        return new BMPImageDecoder();
    }
#endif /* BMP_SUPPORT */
    
#ifdef ICO_SUPPORT
    // ICOs always begin with a 2-byte 0 followed by a 2-byte 1.
    // CURs begin with 2-byte 0 followed by 2-byte 2.
    if (!memcmp(contents, "\000\000\001\000", 4) ||
        !memcmp(contents, "\000\000\002\000", 4))
    {
        return new ICOImageDecoder();
    }
#endif /* ICO_SUPPORT */

#ifdef XBM_SUPPORT
    // XBMs require 8 bytes of info.
    if (length >= 8 && strncmp(contents, "#define ", 8) == 0)
    {
        return new XBMImageDecoder();
    }
#endif /* XBM_SUPPORT */
    // Give up. We don't know what the heck this is.
    
    return 0;
}

ImageSource::ImageSource()
  : m_decoder(0)
{

}

ImageSource::~ImageSource()
{
    clear();
}

void ImageSource::clear()
{
    if (m_decoder) {
        delete m_decoder;
        m_decoder = 0;
    }
}

bool ImageSource::initialized() const
{
    return m_decoder ? true : false;
}

void ImageSource::setData(SharedBuffer* data, bool allDataReceived)
{
    // Make the decoder by sniffing the bytes.
    // This method will examine the data and instantiate an instance of the appropriate decoder plugin.
    // If insufficient bytes are available to determine the image type, no decoder plugin will be
    // made.    
    if (m_decoder)
        delete m_decoder;

    m_decoder = createDecoder(data->buffer());

    if (!m_decoder)
        return;
    m_decoder->setData(data->buffer(), allDataReceived);
}

bool ImageSource::isSizeAvailable()
{
    if (!m_decoder)
        return false;

    return m_decoder->isSizeAvailable();
}

IntSize ImageSource::size() const
{
    if (!m_decoder)
        return IntSize();

    return m_decoder->size();
}

int ImageSource::repetitionCount()
{
    if (!m_decoder)
        return cAnimationNone;

    return m_decoder->repetitionCount();
}

size_t ImageSource::frameCount() const
{
    return m_decoder ? m_decoder->frameCount() : 0;
}

NativeImagePtr ImageSource::createFrameAtIndex(size_t index)
{
    if (!m_decoder || m_decoder->failed())
        return 0;

    PixelsBuffer* buffer = m_decoder->frameBufferAtIndex(index);
#ifdef IMAGE_DISPLAY_ONCE
    if (!buffer || !buffer->bytes().data() || (buffer->status() != PixelsBuffer::FrameComplete))
        return 0;
#else
    if (!buffer || !buffer->bytes().data() || (buffer->status() == PixelsBuffer::FrameEmpty))
        return 0;
#endif

    ImageRef* img = new ImageRef;
	img->source = this;
	img->index = index;
	img->width = size().width();
	img->height = size().height();
	img->pitch = size().width()*pixelPerBytes();

	if (buffer->hasAlpha()) {
		if (pixelFormat() != COLOR_FORMAT_BGRA) {
			img->colorkey = true;
		}
		img->transparent = true;
	}
    return img;
}

float ImageSource::frameDurationAtIndex(size_t index)
{
    if (!m_decoder)
        return 0;

    PixelsBuffer* buffer = m_decoder->frameBufferAtIndex(index);
    if (!buffer || buffer->status() == PixelsBuffer::FrameEmpty)
        return 0;

    return buffer->duration() / 1000.0f;
}

bool ImageSource::frameHasAlphaAtIndex(size_t index)
{
    if (!m_decoder || !m_decoder->supportsAlpha())
        return false;

    PixelsBuffer* buffer = m_decoder->frameBufferAtIndex(index);
    if (!buffer || buffer->status() == PixelsBuffer::FrameEmpty)
        return false;

    return buffer->hasAlpha();
}

bool ImageSource::frameIsCompleteAtIndex(size_t index)
{
    if (!m_decoder)
        return false;

    PixelsBuffer* buffer = m_decoder->frameBufferAtIndex(index);
    return buffer && buffer->status() == PixelsBuffer::FrameComplete;
}

}
