/*
 * GraphicContextDavinci.cpp: GraphicContext implements by davinci.
 *
 * Copyright(C) 2009 ~ 2015 Zhang Ji Peng (onecoolx@gmail.com)
 *
 */

#include "config.h"
#include "GraphicsContext.h"

#include "AffineTransform.h"
#include "NotImplemented.h"
#include "Path.h"
#include "TransformationMatrix.h"
#include <wtf/MathExtras.h>

namespace WebCore {

void GraphicsContext::platformInit(PlatformGraphicsContext* ctx)
{
}

void GraphicsContext::platformDestroy()
{
}

PlatformGraphicsContext* GraphicsContext::platformContext() const
{
}

void GraphicsContext::savePlatformState()
{
}

void GraphicsContext::restorePlatformState()
{
}

void GraphicsContext::setPlatformStrokeColor(const Color&, ColorSpace)
{
}

void GraphicsContext::setPlatformStrokeStyle(StrokeStyle)
{
}

void GraphicsContext::setPlatformStrokeThickness(float)
{
}

void GraphicsContext::setPlatformFillColor(const Color&, ColorSpace)
{
}

void GraphicsContext::setPlatformShouldAntialias(bool)
{
}

void GraphicsContext::setPlatformShadow(const FloatSize&, float blur, const Color&, ColorSpace)
{
}

void GraphicsContext::clearPlatformShadow()
{
}

void GraphicsContext::setPlatformCompositeOperation(CompositeOperator, BlendMode)
{
}

void GraphicsContext::beginPlatformTransparencyLayer(float opacity)
{
}

void GraphicsContext::endPlatformTransparencyLayer()
{
}

bool GraphicsContext::supportsTransparencyLayers()
{
    return true;
}

void GraphicsContext::setURLForRect(const KURL&, const IntRect&)
{
    notImplemented();
}

void GraphicsContext::setCTM(const AffineTransform&)
{
}

void GraphicsContext::concatCTM(const AffineTransform& transform)
{
}

AffineTransform GraphicsContext::getCTM(IncludeDeviceScale) const
{
}

void GraphicsContext::canvasClip(const Path&, WindRule)
{
}

void GraphicsContext::fillRoundedRect(const IntRect&, const IntSize& topLeft, const IntSize& topRight,
                                      const IntSize& bottomLeft, const IntSize& bottomRight, const Color&, ColorSpace)
{
}

void GraphicsContext::setImageInterpolationQuality(InterpolationQuality)
{
}

InterpolationQuality GraphicsContext::imageInterpolationQuality() const
{
}

void GraphicsContext::setAlpha(float alpha)
{
}

void GraphicsContext::fillRect(const FloatRect& rect)
{
}

void GraphicsContext::fillRect(const FloatRect& rect, const Color& color, ColorSpace)
{
}

void GraphicsContext::strokeRect(const FloatRect& rect, float width)
{
}

void GraphicsContext::clipOut(const Path& path)
{
}

void GraphicsContext::clipOut(const IntRect& r)
{
}

void GraphicsContext::clip(const FloatRect& rect)
{
}

void GraphicsContext::clip(const Path& path, WindRule windRule)
{
}

void GraphicsContext::clipPath(const Path& path, WindRule clipRule)
{
}

void GraphicsContext::clipConvexPolygon(size_t numPoints, const FloatPoint* points, bool antialiased)
{
}

void GraphicsContext::clearRect(const FloatRect& rect)
{
}

void GraphicsContext::fillPath(const Path& path)
{
}

void GraphicsContext::strokePath(const Path& path)
{
}

void GraphicsContext::translate(float x, float y)
{
}

void GraphicsContext::scale(const FloatSize& size)
{
}

void GraphicsContext::rotate(float radians)
{
}

FloatRect GraphicsContext::roundToDevicePixels(const FloatRect& frect, RoundingMode)
{
}

void GraphicsContext::setMiterLimit(float miter)
{
}

void GraphicsContext::setLineDash(const DashArray& dashes, float dashOffset)
{
}

void GraphicsContext::setLineCap(LineCap lineCap)
{
}

void GraphicsContext::setLineJoin(LineJoin lineJoin)
{
}

void GraphicsContext::drawFocusRing(const Vector<IntRect>& rects, int width, int offset, const Color& color)
{
}

void GraphicsContext::drawFocusRing(const Path& path, int width, int offset, const Color& color)
{
}

void GraphicsContext::drawConvexPolygon(size_t npoints, const FloatPoint* points, bool shouldAntialias)
{
}

void GraphicsContext::drawLine(const IntPoint& point1, const IntPoint& point2)
{
}

void GraphicsContext::drawRect(const IntRect& rect)
{
}

void GraphicsContext::drawEllipse(const IntRect& rect)
{
}

void GraphicsContext::drawLineForText(const FloatPoint& origin, float width, bool)
{
}

void GraphicsContext::drawLineForDocumentMarker(const FloatPoint& origin, float width, DocumentMarkerLineStyle style)
{
}

#if ENABLE(3D_RENDERING) && USE(TEXTURE_MAPPER)
TransformationMatrix GraphicsContext::get3DTransform() const
{
    return getCTM().toTransformationMatrix();
}

void GraphicsContext::concat3DTransform(const TransformationMatrix& transform)
{
    concatCTM(transform.toAffineTransform());
}

void GraphicsContext::set3DTransform(const TransformationMatrix& transform)
{
    setCTM(transform.toAffineTransform());
}
#endif
}
