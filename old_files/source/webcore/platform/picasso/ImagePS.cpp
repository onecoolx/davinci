/*
** ImagePS.cpp: Image implements by picasso.
**
** Copyright(C) 2009 Zhang Ji Peng (onecoolx@gmail.com)
**
*/
#include "config.h"
#include "picasso.h"
#include "Image.h"
#include "BitmapImage.h"
#include "ImageObserver.h"
#include "ImageDecoder.h"
#include "GraphicsContext.h"
#include "AffineTransform.h"
#include "wtf/MathExtras.h"
#include "Debug.h"

PassRefPtr<WebCore::SharedBuffer> loadResourceIntoBuffer(const char*);

namespace WebCore {

void FrameData::clear()
{
    if (m_frame) {
        delete m_frame;
        m_frame = 0;
        m_duration = 0.;
        m_hasAlpha = true;
    }
}

void BitmapImage::initPlatformData()
{
}

void BitmapImage::invalidatePlatformData()
{
}

Image* Image::loadPlatformResource(const char *name)
{
    RefPtr<SharedBuffer> buffer = loadResourceIntoBuffer(name);
    BitmapImage* img = new BitmapImage;
    img->setData(buffer.release(), true);
    return img;
}

static ps_composite get_com_op(CompositeOperator op)
{
    switch (op) {
        case CompositeClear:
            return COMPOSITE_CLEAR;
        case CompositeCopy:
            return COMPOSITE_SRC;
        case CompositeSourceOver:
            return COMPOSITE_SRC_OVER;
        case CompositeSourceIn:
            return COMPOSITE_SRC_IN;
        case CompositeSourceOut:
            return COMPOSITE_SRC_OUT;
        case CompositeSourceAtop:
            return COMPOSITE_SRC_ATOP;
        case CompositeDestinationOver:
            return COMPOSITE_DST_OVER;
        case CompositeDestinationIn:
            return COMPOSITE_DST_IN;
        case CompositeDestinationOut:
            return COMPOSITE_DST_OUT;
        case CompositeDestinationAtop:
            return COMPOSITE_DST_ATOP;
        case CompositeXOR:
            return COMPOSITE_XOR;
        case CompositePlusDarker:
            return COMPOSITE_DARKEN;
        case CompositeHighlight:
            return COMPOSITE_PLUS;
        case CompositePlusLighter:
            return COMPOSITE_LIGHTEN;
        default:
            return COMPOSITE_SRC_OVER;
    }
}

static ps_image* build_image(NativeImagePtr imgref)
{
	if (!imgref->source->initialized())
		return 0;

    PixelsBuffer* buffer = imgref->source->decoder()->frameBufferAtIndex(imgref->index);
	ps_image* img = ps_image_create_with_data(buffer->bytes().data(), pixelFormat(),
												imgref->width, imgref->height, imgref->pitch);

	if (img) {
		if (imgref->transparent) {
			if (imgref->colorkey) {
				ps_color c = {0,0,0,0};
				ps_image_set_transparent_color(img, &c);
			}
			ps_image_set_allow_transparent(img, True);
		}
	}
	return img;
}

void Image::drawPattern(GraphicsContext* context, const FloatRect& tileRect, const AffineTransform& patternTransform,
                        const FloatPoint& p, CompositeOperator op, const FloatRect& dst)
{
    NativeImagePtr imgref = nativeImageForCurrentFrame();
    if (!imgref)
        return;

	ps_image * img = build_image(imgref);
	if (img) {
		ps_context * gc = context->platformContext(); 
		ps_composite com_op = ps_set_composite_operator(gc, get_com_op(op));

		ps_rect rect = {tileRect.x(), tileRect.y(), tileRect.width(), tileRect.height()};
		ps_image* pimg = ps_image_create_from_image(img, &rect);

		if (tileRect.size() == dst.size() && !p.x() && !p.y()) { //For optimization with single image
			ps_set_source_image(gc, pimg);
			//draw image
			ps_rect drect = {dst.x(), dst.y(), dst.width(), dst.height()};
			ps_rectangle(gc, &drect);
			ps_fill(gc);
		} else {
			//create tile image
			ps_matrix* mtx = ps_matrix_create_copy(patternTransform.platformTransform());
			ps_matrix_translate (mtx, p.x()-dst.x(), p.y()-dst.y());

			ps_pattern* pattern = ps_pattern_create_image(pimg, WRAP_TYPE_REPEAT, WRAP_TYPE_REPEAT, mtx);
			ps_set_source_pattern(gc, pattern);

			//draw pattern
			ps_rect drect = {dst.x(), dst.y(), dst.width(), dst.height()};
			ps_rectangle(gc, &drect);
			ps_fill(gc);

			//destory pattern objects
			ps_pattern_unref(pattern);
			ps_matrix_unref(mtx);
		}
		ps_image_unref(pimg);
		(void)ps_set_composite_operator(gc, com_op);

		ps_image_unref(img);
	}

	if (imageObserver())
		imageObserver()->didDraw(this);
}

void BitmapImage::draw(GraphicsContext* context, const FloatRect& dst, const FloatRect& src, CompositeOperator op)
{  
	startAnimation();

    NativeImagePtr imgref = nativeImageForCurrentFrame();
	if (!imgref)
		return;

	ps_image * img = build_image(imgref);
    if (img) {
        ps_context * gc = context->platformContext(); 
		ps_rect rect = {src.x(), src.y(), src.width(), src.height()};
		ps_rect drect = {dst.x(), dst.y(), dst.width(), dst.height()};
		if ((dst.size() == src.size()) && (op == CompositeSourceOver) 
			&& (!imgref->transparent)) {
			//For optimization with single image
			ps_point point = {drect.x, drect.y};
			ps_world_to_viewport(gc, &point);
			ps_canvas* src_canvas = ps_canvas_create_from_image(img, 0);
			ps_canvas* dst_canvas = ps_context_get_canvas(gc); 
			ps_canvas_bitblt(src_canvas, &rect, dst_canvas, &point);
			ps_canvas_unref(src_canvas);
		} else {
			ps_composite com_op = ps_set_composite_operator(gc, get_com_op(op));
			ps_image* pimg = ps_image_create_from_image(img, &rect);
			ps_set_source_image(gc, pimg);
			ps_rectangle(gc, &drect);
			ps_fill(gc);
			(void)ps_set_composite_operator(gc, com_op);
			ps_image_unref(pimg);
		}
		ps_image_unref(img);
    }

	if (imageObserver())
		imageObserver()->didDraw(this);
}

void BitmapImage::checkForSolidColor()
{
    m_isSolidColor = false;
}

}
