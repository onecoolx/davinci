/*
 * ImageBufferDavinci.cpp: ImageBuffer implements by davinci.
 *
 * Copyright(C) 2015 Zhang Ji Peng (onecoolx@gmail.com)
 *
 */

#include "config.h"
#include "ImageBuffer.h"

#include "BitmapImage.h"
#include "HostWindow.h"
#include "ImageData.h"

#include <wtf/Vector.h>
#include <wtf/text/Base64.h>
#include <wtf/text/WTFString.h>

using namespace std;

namespace WebCore {

ImageBufferData::ImageBufferData(const IntSize& size)
	: m_size(size)
{
}

void ImageBufferData::getImageData(GraphicsContext* context, const IntRect& rect, const IntRect& size, unsigned char* result, bool unmultiply) const
{
}

void ImageBufferData::draw(GraphicsContext* thisContext, GraphicsContext* otherContext, ColorSpace styleColorSpace, const FloatRect& destRect, const FloatRect& srcRect, CompositeOperator op, bool useLowQualityScale) const
{
}

ImageBuffer::ImageBuffer(const IntSize& size, float, ColorSpace, RenderingMode renderingMode, bool& success)
    : m_data(size)
	, m_size(size)
    , m_logicalSize(size)
    , m_resolutionScale(1)
{
}

ImageBuffer::~ImageBuffer()
{
}

GraphicsContext* ImageBuffer::context() const
{
	return 0;
}

BackingStoreCopy ImageBuffer::fastCopyImageMode()
{
    return DontCopyBackingStore;
}

PlatformLayer* ImageBuffer::platformLayer() const
{
	return 0;
}

PassRefPtr<Image> ImageBuffer::copyImage(BackingStoreCopy, ScaleBehavior) const
{
	return 0;
}

void ImageBuffer::clip(GraphicsContext* context, const FloatRect& rect) const
{
}

void ImageBuffer::draw(GraphicsContext* context, ColorSpace styleColorSpace, const FloatRect& destRect, const FloatRect& srcRect, CompositeOperator op, BlendMode, bool useLowQualityScale)
{
    m_data.draw(m_context.get(), context, styleColorSpace, destRect, srcRect, op, useLowQualityScale);
}

void ImageBuffer::drawPattern(GraphicsContext* context, const FloatRect& srcRect, const AffineTransform& patternTransform, const FloatPoint& phase, ColorSpace styleColorSpace, CompositeOperator op, const FloatRect& destRect)
{
    RefPtr<Image> image = copyImage(DontCopyBackingStore);
    image->drawPattern(context, srcRect, patternTransform, phase, styleColorSpace, op, destRect);
}

void ImageBuffer::platformTransformColorSpace(const Vector<int>&)
{
}

PassRefPtr<Uint8ClampedArray> ImageBuffer::getUnmultipliedImageData(const IntRect& rect, CoordinateSystem) const
{
    RefPtr<Uint8ClampedArray> result = Uint8ClampedArray::createUninitialized(rect.width() * rect.height() * 4);
    m_data.getImageData(m_context.get(), rect, IntRect(IntPoint(0, 0), m_size), result->data(), true);
    return result;
}

PassRefPtr<Uint8ClampedArray> ImageBuffer::getPremultipliedImageData(const IntRect& rect, CoordinateSystem) const
{
    RefPtr<Uint8ClampedArray> result = Uint8ClampedArray::createUninitialized(rect.width() * rect.height() * 4);
    m_data.getImageData(m_context.get(), rect, IntRect(IntPoint(0, 0), m_size), result->data(), false);
    return result;
}

void ImageBuffer::putByteArray(Multiply multiplied, Uint8ClampedArray* source, const IntSize& sourceSize, const IntRect& sourceRect, const IntPoint& destPoint, CoordinateSystem)
{
}

String ImageBuffer::toDataURL(const String& mimeType, const double* quality, CoordinateSystem) const
{
    if (m_size.isEmpty())
        return "data:,";

#if 0
    enum {
        EncodeJPEG,
        EncodePNG,
    } encodeType = mimeType.lower() == "image/png" ? EncodePNG : EncodeJPEG;

    // According to http://www.w3.org/TR/html5/the-canvas-element.html,
    // "For image types that do not support an alpha channel, the image must be"
    // "composited onto a solid black background using the source-over operator,"
    // "and the resulting image must be the one used to create the data: URL."
    // JPEG doesn't have alpha channel, so we need premultiplied data.
    RefPtr<Uint8ClampedArray> imageData = encodeType == EncodePNG
        ? getUnmultipliedImageData(IntRect(IntPoint(0, 0), m_size))
        : getPremultipliedImageData(IntRect(IntPoint(0, 0), m_size));

    Vector<char> output;
    const char* header;
    if (encodeType == EncodePNG) {
        if (!compressRGBABigEndianToPNG(imageData->data(), m_size, output))
            return "data:,";
        header = "data:image/png;base64,";
    } else {
        if (!compressRGBABigEndianToJPEG(imageData->data(), m_size, output, quality))
            return "data:,";
        header = "data:image/jpeg;base64,";
    }

    Vector<char> base64;
    base64Encode(output, base64);

    output.clear();

    Vector<char> url;
    url.append(header, strlen(header));
    url.append(base64);

    return String(url.data(), url.size());
#endif
}

} // namespace WebCore
