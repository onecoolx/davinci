/*
 * BitmapImageDavinci.h: BitmapImage implements by davinci.
 *
 * Copyright(C) 2015 Zhang Ji Peng (onecoolx@gmail.com)
 *
 */

#include "config.h"
#include "BitmapImage.h"

#include "FloatRect.h"
#include "ImageObserver.h"

namespace WebCore {

BitmapImage::BitmapImage(PassNativeImagePtr nativeImage, ImageObserver* observer)
    : Image(observer)
    //, m_size(cairoSurfaceSize(nativeImage.get()))
    , m_currentFrame(0)
    , m_frames(0)
    , m_frameTimer(0)
    , m_repetitionCount(cAnimationNone)
    , m_repetitionCountStatus(Unknown)
    , m_repetitionsComplete(0)
    , m_decodedSize(0)
    , m_frameCount(1)
    , m_isSolidColor(false)
    , m_checkedForSolidColor(false)
    , m_animationFinished(true)
    , m_allDataReceived(true)
    , m_haveSize(true)
    , m_sizeAvailable(true)
    , m_haveFrameCount(true)
{
    m_decodedSize = m_size.width() * m_size.height() * 4;

    m_frames.grow(1);
    //m_frames[0].m_hasAlpha = cairo_surface_get_content(nativeImage.get()) != CAIRO_CONTENT_COLOR;
    m_frames[0].m_frame = nativeImage;
    m_frames[0].m_haveMetadata = true;
    checkForSolidColor();
}

void BitmapImage::draw(GraphicsContext* context, const FloatRect& dst, const FloatRect& src, ColorSpace styleColorSpace, CompositeOperator op, BlendMode blendMode)
{
    draw(context, dst, src, styleColorSpace, op, blendMode, ImageOrientationDescription());
}

void BitmapImage::draw(GraphicsContext* context, const FloatRect& dst, const FloatRect& src, ColorSpace styleColorSpace, CompositeOperator op,
    BlendMode blendMode, ImageOrientationDescription description)
{
    if (!dst.width() || !dst.height() || !src.width() || !src.height())
        return;

    startAnimation();

#if 0
    RefPtr<cairo_surface_t> surface = frameAtIndex(m_currentFrame);
    if (!surface) // If it's too early we won't have an image yet.
        return;

    if (mayFillWithSolidColor()) {
        fillWithSolidColor(context, dst, solidColor(), styleColorSpace, op);
        return;
    }

    context->save();

    // Set the compositing operation.
    if (op == CompositeSourceOver && blendMode == BlendModeNormal && !frameHasAlphaAtIndex(m_currentFrame))
        context->setCompositeOperation(CompositeCopy);
    else
        context->setCompositeOperation(op, blendMode);

#if ENABLE(IMAGE_DECODER_DOWN_SAMPLING)
    IntSize scaledSize = cairoSurfaceSize(surface.get());
    FloatRect adjustedSrcRect = adjustSourceRectForDownSampling(src, scaledSize);
#else
    FloatRect adjustedSrcRect(src);
#endif

    ImageOrientation orientation;
    if (description.respectImageOrientation() == RespectImageOrientation)
        orientation = frameOrientationAtIndex(m_currentFrame);

    FloatRect dstRect = dst;

    if (orientation != DefaultImageOrientation) {
        // ImageOrientation expects the origin to be at (0, 0).
        context->translate(dstRect.x(), dstRect.y());
        dstRect.setLocation(FloatPoint());
        context->concatCTM(orientation.transformFromDefault(dstRect.size()));
        if (orientation.usesWidthAsHeight()) {
            // The destination rectangle will have it's width and height already reversed for the orientation of
            // the image, as it was needed for page layout, so we need to reverse it back here.
            dstRect = FloatRect(dstRect.x(), dstRect.y(), dstRect.height(), dstRect.width());
        }
    }

    context->platformContext()->drawSurfaceToContext(surface.get(), dstRect, adjustedSrcRect, context);

    context->restore();
#endif

    if (imageObserver())
        imageObserver()->didDraw(this);
}

void BitmapImage::checkForSolidColor()
{
    m_isSolidColor = false;
    m_checkedForSolidColor = true;

    if (frameCount() > 1)
        return;

#if 0
    RefPtr<cairo_surface_t> surface = frameAtIndex(m_currentFrame);
    if (!surface) // If it's too early we won't have an image yet.
        return;

    if (cairo_surface_get_type(surface.get()) != CAIRO_SURFACE_TYPE_IMAGE)
        return;

    IntSize size = cairoSurfaceSize(surface.get());

    if (size.width() != 1 || size.height() != 1)
        return;

    unsigned* pixelColor = reinterpret_cast_ptr<unsigned*>(cairo_image_surface_get_data(surface.get()));
    m_solidColor = colorFromPremultipliedARGB(*pixelColor);

    m_isSolidColor = true;
#endif
}

void BitmapImage::invalidatePlatformData()
{
}

bool FrameData::clear(bool clearMetadata)
{
    if (clearMetadata)
        m_haveMetadata = false;

#if 0
    if (m_frame) {
        m_frame.clear();
        return true;
    }
#endif
    return false;
}

} // namespace WebCore

