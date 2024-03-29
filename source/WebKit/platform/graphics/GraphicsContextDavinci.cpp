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

#include <picasso.h>

namespace WebCore {

struct TransparentLayer {
    TransparentLayer(ps_canvas* p, float o)
        : canvas(p)
        , opacity(o)
    {
    }

    ps_canvas* canvas;
    float opacity;
};

class GraphicsContextPlatformPrivate
{
public:
    GraphicsContextPlatformPrivate() : context(0) { }
    ~GraphicsContextPlatformPrivate() { }

    ps_context* context;
    Vector<TransparentLayer> layers;
};

static inline ps_color make_color(const Color& c)
{
    ps_color color;
    color.r = (float)c.red()/255.0f;
    color.g = (float)c.green()/255.0f;
    color.b = (float)c.blue()/255.0f;
    color.a = (float)c.alpha()/255.0f;
    return color;
}

static void draw_graphic(ps_context* gc, bool fill, bool stroke)
{
    if (fill && stroke)
        ps_paint(gc);
    else if (fill && !stroke)
        ps_fill(gc);
    else if (!fill && stroke)
        ps_stroke(gc);
}

static inline void setPenColor(ps_context* gc, const Color& col)
{
    ps_color sc = make_color(col);
    ps_set_stroke_color(gc, &sc);
}

static inline void setBrushColor(ps_context* gc, const Color& col)
{
    ps_color fc = make_color(col);
    ps_set_source_color(gc, &fc);
}

// A fillRect helper
static inline void fillRectSourceOver(ps_context* gc, const FloatRect& rect, const Color& col)
{
    setBrushColor(gc, col);
    ps_rect r = {rect.x(), rect.y(), rect.width(), rect.height()};
    ps_composite op = ps_set_composite_operator(gc, COMPOSITE_SRC_OVER);
    ps_rectangle(gc, &r);
    ps_fill(gc);
    ps_set_composite_operator(gc, op);
}

void GraphicsContext::platformInit(PlatformGraphicsContext* ctx)
{
    m_data = new GraphicsContextPlatformPrivate();
    if (ctx) {
        m_data->context = ps_context_ref(ctx);
    } else {
        setPaintingDisabled(true);
    }
}

void GraphicsContext::platformDestroy()
{
    if (m_data->context) {
        ps_context_unref(m_data->context);
        m_data->context = 0;
    }
    delete m_data;
}

PlatformGraphicsContext* GraphicsContext::platformContext() const
{
    return m_data->context;
}

void GraphicsContext::savePlatformState()
{
    ps_save(m_data->context);
}

void GraphicsContext::restorePlatformState()
{
    ps_restore(m_data->context);
}

void GraphicsContext::setPlatformStrokeColor(const Color& color, ColorSpace)
{
    if (paintingDisabled())
        return;
    setPenColor(m_data->context, color);
}

void GraphicsContext::setPlatformStrokeStyle(StrokeStyle strokeStyle)
{
    static float dashPattern[] = {5.0, 5.0};
    static float dotPattern[] = {1.0, 1.0};

    if (paintingDisabled())
        return;

    switch (strokeStyle) {
        case NoStroke:
            break;
        case SolidStroke:
#if ENABLE(CSS3_TEXT)
        case DoubleStroke:
        case WavyStroke:
#endif // CSS3_TEXT
            ps_reset_line_dash(m_data->context);
            break;
        case DottedStroke:
            ps_set_line_dash(m_data->context, 0, dotPattern, 2);
            break;
        case DashedStroke:
            ps_set_line_dash(m_data->context, 0, dashPattern, 2);
            break;
    }
}

void GraphicsContext::setPlatformStrokeThickness(float width)
{
    if (paintingDisabled())
        return;
    ps_set_line_width(m_data->context, width);
}

void GraphicsContext::setPlatformFillColor(const Color& fill, ColorSpace)
{
    if (paintingDisabled())
        return;
    setBrushColor(m_data->context, fill);
}

void GraphicsContext::setPlatformShouldAntialias(bool enable)
{
    if (paintingDisabled())
        return;
    ps_set_antialias(m_data->context, enable ? True : False);
}

void GraphicsContext::setPlatformShadow(const FloatSize& size, float blur, const Color& color, ColorSpace)
{
    if (paintingDisabled())
        return;

    ps_color c = make_color(color);
    ps_set_shadow(m_data->context, size.width(), size.height(), (float)blur/40);
    ps_set_shadow_color(m_data->context, &c);
}

void GraphicsContext::clearPlatformShadow()
{
    if (paintingDisabled())
        return;
    ps_reset_shadow(m_data->context);
}

void GraphicsContext::setPlatformCompositeOperation(CompositeOperator op, BlendMode blendOp)
{
    if (paintingDisabled())
        return;

    ps_context* gc = m_data->context;

    if (blendOp == BlendModeNormal) {
        // composite
        switch (op) {
            case CompositeClear:
                ps_set_composite_operator(gc, COMPOSITE_CLEAR);
                break;
            case CompositeCopy:
                ps_set_composite_operator(gc, COMPOSITE_SRC);
                break;
            case CompositeSourceOver:
                ps_set_composite_operator(gc, COMPOSITE_SRC_OVER);
                break;
            case CompositeSourceIn:
                ps_set_composite_operator(gc, COMPOSITE_SRC_IN);
                break;
            case CompositeSourceOut:
                ps_set_composite_operator(gc, COMPOSITE_SRC_OUT);
                break;
            case CompositeSourceAtop:
                ps_set_composite_operator(gc, COMPOSITE_SRC_ATOP);
                break;
            case CompositeDestinationOver:
                ps_set_composite_operator(gc, COMPOSITE_DST_OVER);
                break;
            case CompositeDestinationIn:
                ps_set_composite_operator(gc, COMPOSITE_DST_IN);
                break;
            case CompositeDestinationOut:
                ps_set_composite_operator(gc, COMPOSITE_DST_OUT);
                break;
            case CompositeDestinationAtop:
                ps_set_composite_operator(gc, COMPOSITE_DST_ATOP);
                break;
            case CompositeXOR:
                ps_set_composite_operator(gc, COMPOSITE_XOR);
                break;
            case CompositePlusDarker:
                ps_set_composite_operator(gc, COMPOSITE_DARKEN);
                break;
            case CompositePlusLighter:
                ps_set_composite_operator(gc, COMPOSITE_LIGHTEN);
                break;
            case CompositeDifference:
                ps_set_composite_operator(gc, COMPOSITE_DIFFERENCE);
                break;
            default:
                ps_set_composite_operator(gc, COMPOSITE_SRC_OVER);
                break;
        }
    } else {
        // blend mode
        switch (blendOp) {
            case BlendModeMultiply:
                ps_set_composite_operator(gc, COMPOSITE_MULTIPLY);
                break;
            case BlendModeScreen:
                ps_set_composite_operator(gc, COMPOSITE_SCREEN);
                break;
            case BlendModeOverlay:
                ps_set_composite_operator(gc, COMPOSITE_OVERLAY);
                break;
            case BlendModeDarken:
                ps_set_composite_operator(gc, COMPOSITE_DARKEN);
                break;
            case BlendModeLighten:
                ps_set_composite_operator(gc, COMPOSITE_LIGHTEN);
                break;
            case BlendModeColorDodge:
                ps_set_composite_operator(gc, COMPOSITE_DODGE);
                break;
            case BlendModeColorBurn:
                ps_set_composite_operator(gc, COMPOSITE_BURN);
                break;
            case BlendModeHardLight:
                ps_set_composite_operator(gc, COMPOSITE_HARDLIGHT);
                break;
            case BlendModeSoftLight:
                ps_set_composite_operator(gc, COMPOSITE_SOFTLIGHT);
                break;
            case BlendModeDifference:
                ps_set_composite_operator(gc, COMPOSITE_DIFFERENCE);
                break;
            case BlendModeExclusion:
                ps_set_composite_operator(gc, COMPOSITE_EXCLUSION);
                break;
            case BlendModeHue:
                ps_set_composite_operator(gc, COMPOSITE_HUE);
                break;
            case BlendModeSaturation:
                ps_set_composite_operator(gc, COMPOSITE_SATURATION);
                break;
            case BlendModeColor:
                ps_set_composite_operator(gc, COMPOSITE_COLOR);
                break;
            case BlendModeLuminosity:
                ps_set_composite_operator(gc, COMPOSITE_LUMINOSITY);
                break;
            default:
                ps_set_composite_operator(gc, COMPOSITE_SRC_OVER);
                break;
        }
    }
}

void GraphicsContext::beginPlatformTransparencyLayer(float opacity)
{
    if (paintingDisabled())
        return;

    ps_canvas* pc = ps_context_get_canvas(m_data->context);
    ps_canvas* layer = ps_canvas_create_compatible(pc, -1, -1);
    pc = ps_context_set_canvas(m_data->context, layer);
    m_data->layers.append(TransparentLayer(pc, opacity));
}

void GraphicsContext::endPlatformTransparencyLayer()
{
    if (paintingDisabled())
        return;

    TransparentLayer tlayer = m_data->layers.last();
    float opacity = tlayer.opacity;
    ps_canvas* pc = tlayer.canvas;
    m_data->layers.removeLast();

    ps_size size = { 0, 0 };
    ps_canvas* layer = ps_context_set_canvas(m_data->context, pc);
    ps_canvas_get_size(layer, &size);

    ps_save(m_data->context);
    ps_set_source_canvas(m_data->context, layer);
    ps_set_alpha(m_data->context, opacity);
    ps_rect rc = { 0, 0, size.w, size.h };
    ps_rectangle(m_data->context, &rc);
    ps_fill(m_data->context);
    ps_restore(m_data->context);

    ps_canvas_unref(layer);
}

bool GraphicsContext::supportsTransparencyLayers()
{
    return true;
}

void GraphicsContext::setURLForRect(const KURL&, const IntRect&)
{
    notImplemented();
}

void GraphicsContext::setCTM(const AffineTransform& transform)
{
    if (paintingDisabled())
        return;
    ps_set_matrix(m_data->context, transform.platformTransform());
}

void GraphicsContext::concatCTM(const AffineTransform& transform)
{
    if (paintingDisabled())
        return;
    ps_transform(m_data->context, transform.platformTransform());
}

AffineTransform GraphicsContext::getCTM(IncludeDeviceScale) const
{
    if (paintingDisabled())
        return AffineTransform();

    ps_matrix* m = ps_matrix_create();
    ps_get_matrix(m_data->context, m);
    AffineTransform mtx(m);
    ps_matrix_unref(m);
    return mtx;
}

void GraphicsContext::canvasClip(const Path& path, WindRule windRule)
{
    clip(path, windRule);
}

void GraphicsContext::fillRoundedRect(const IntRect& rc, const IntSize& topLeft, const IntSize& topRight,
        const IntSize& bottomLeft, const IntSize& bottomRight, const Color& color, ColorSpace)
{
    if (paintingDisabled())
        return;

    if (color.alpha()) {
        setBrushColor(m_data->context, color);
        ps_rect r = {rc.x(), rc.y(), rc.width(), rc.height()};
        ps_rounded_rect(m_data->context, &r, topLeft.width(), topLeft.height(), topRight.width(),
                topRight.height(), bottomLeft.width(), bottomLeft.height(), bottomRight.width(), bottomRight.height());
        ps_fill(m_data->context);
    }
}

void GraphicsContext::setImageInterpolationQuality(InterpolationQuality quality)
{
    if (paintingDisabled())
        return;

    switch (quality) {
        case InterpolationNone:
        case InterpolationLow:
            ps_set_filter(m_data->context, FILTER_NEAREST);
            break;
        case InterpolationMedium:
        case InterpolationDefault:
            ps_set_filter(m_data->context, FILTER_BILINEAR);
            break;
        case InterpolationHigh:
            ps_set_filter(m_data->context, FILTER_GAUSSIAN);
            break;
    }
}

InterpolationQuality GraphicsContext::imageInterpolationQuality() const
{
    if (paintingDisabled())
        return InterpolationDefault;

    InterpolationQuality quality;  
    ps_filter f = ps_set_filter(m_data->context, FILTER_BILINEAR);

    switch (f) {
        case FILTER_BILINEAR:
            quality = InterpolationDefault;
            break;
        case FILTER_NEAREST:
            quality = InterpolationLow;
            break;
        case FILTER_GAUSSIAN:
            quality = InterpolationHigh;
            break;
    }
    ps_set_filter(m_data->context, f);
    return quality;
}

void GraphicsContext::setAlpha(float alpha)
{
    if (paintingDisabled())
        return;
    ps_set_alpha(m_data->context, alpha);
}

void GraphicsContext::fillRect(const FloatRect& rect)
{
    if (paintingDisabled())
        return;

    if (m_state.fillGradient) {
        m_state.fillGradient->fill(this, rect);
    } else if (m_state.fillPattern) {
        m_state.fillPattern->fill(this, rect);
    } else {
        ps_rect r = { rect.x(), rect.y(), rect.width(), rect.height() };
        ps_rectangle(m_data->context, &r);
        ps_fill(m_data->context);
    }
}

void GraphicsContext::fillRect(const FloatRect& rect, const Color& color, ColorSpace)
{
    if (paintingDisabled())
        return;

    if (color.alpha()) {
        fillRectSourceOver(m_data->context, rect, color);
    }
}

void GraphicsContext::strokeRect(const FloatRect& rect, float width)
{
    if (paintingDisabled())
        return;

    ps_context* gc = m_data->context;
    float oldwidth = ps_set_line_width(gc, width);

    if (m_state.strokeGradient) {
        m_state.strokeGradient->stroke(this, rect);
    } else if (m_state.strokePattern) {
        m_state.strokePattern->stroke(this, rect);
    } else {
        ps_rect r = { rect.x(), rect.y(), rect.width(), rect.height() };
        ps_rectangle(gc, &r);
        ps_stroke(gc);
    }
    ps_set_line_width(gc, oldwidth);
}

void GraphicsContext::clipOut(const Path& path)
{
    if (paintingDisabled())
        return;

    ps_size size = { 0, 0 };
    ps_canvas* pc = ps_context_get_canvas(m_data->context);
    if (!ps_canvas_get_size(pc, &size))
        return;

    ps_rect rc = { 0, 0, size.w, size.h };
    ps_rectangle(m_data->context, &rc);
    ps_add_sub_path(m_data->context, path.platformPath());
    ps_fill_rule old_rule = ps_set_fill_rule(m_data->context, FILL_RULE_EVEN_ODD);
    ps_clip(m_data->context);
    ps_set_fill_rule(m_data->context, old_rule);
}

void GraphicsContext::clipOut(const IntRect& r)
{
    if (paintingDisabled())
        return;

    ps_size size = { 0, 0 };
    ps_canvas* pc = ps_context_get_canvas(m_data->context);
    if (!ps_canvas_get_size(pc, &size))
        return;

    ps_rect rc = { 0, 0, size.w, size.h };
    ps_rect rt = { r.x(), r.y(), r.width(), r.height() };
    ps_rectangle(m_data->context, &rc);
    ps_rectangle(m_data->context, &rt);
    ps_fill_rule old_rule = ps_set_fill_rule(m_data->context, FILL_RULE_EVEN_ODD);
    ps_clip(m_data->context);
    ps_set_fill_rule(m_data->context, old_rule);
}

void GraphicsContext::clip(const FloatRect& rect)
{
    if (paintingDisabled())
        return;

    ps_rect rt = { rect.x(), rect.y(), rect.width(), rect.height() };
    ps_clip_device_rect(m_data->context, &rt);
}

void GraphicsContext::clip(const Path& path, WindRule windRule)
{
    if (paintingDisabled())
        return;

    ps_add_sub_path(m_data->context, path.platformPath());
    ps_fill_rule old_rule = ps_set_fill_rule(m_data->context, windRule == RULE_EVENODD ? FILL_RULE_EVEN_ODD : FILL_RULE_WINDING);
    ps_clip(m_data->context);
    ps_set_fill_rule(m_data->context, old_rule);
}

void GraphicsContext::clipPath(const Path& path, WindRule clipRule)
{
    if (paintingDisabled())
        return;
    ps_clip_path(m_data->context, path.platformPath(), clipRule == RULE_EVENODD ? FILL_RULE_EVEN_ODD : FILL_RULE_WINDING);
}

void GraphicsContext::clipConvexPolygon(size_t numPoints, const FloatPoint* points, bool antialiased)
{
    if (paintingDisabled())
        return;

    if (numPoints <= 1)
        return;

    ps_context* gc = m_data->context;
    ps_new_path(gc);
    ps_point p = { points[0].x(), points[0].y() };
    ps_move_to(gc, &p);
    for (size_t i = 1; i < numPoints; i++) {
        p.x = points[i].x(); p.y = points[i].y();
        ps_line_to(gc, &p);
    }
    ps_close_path(gc);

    ps_fill_rule oldRule = ps_set_fill_rule(gc, FILL_RULE_WINDING);
    ps_clip(gc);
    ps_set_fill_rule(gc, oldRule);
}

void GraphicsContext::clearRect(const FloatRect& rect)
{
    if (paintingDisabled())
        return;

    ps_save(m_data->context);
    ps_color c = { 0, 0, 0, 0 };
    ps_rect r = { rect.x(), rect.y(), rect.width(), rect.height() };
    ps_clip_device_rect(m_data->context, &r);
    ps_set_source_color(m_data->context, &c);
    ps_clear(m_data->context);
    ps_restore(m_data->context);
}

void GraphicsContext::fillPath(const Path& path)
{
    if (paintingDisabled())
        return;
    ps_set_path(m_data->context, path.platformPath());
    ps_fill(m_data->context);
}

void GraphicsContext::strokePath(const Path& path)
{
    if (paintingDisabled())
        return;
    ps_set_path(m_data->context, path.platformPath());
    ps_stroke(m_data->context);
}

void GraphicsContext::translate(float x, float y)
{
    if (paintingDisabled())
        return;
    ps_translate(m_data->context, x, y);
}

void GraphicsContext::scale(const FloatSize& size)
{
    if (paintingDisabled())
        return;
    ps_scale(m_data->context, size.width(), size.height());
}

void GraphicsContext::rotate(float radians)
{
    if (paintingDisabled())
        return;
    ps_rotate(m_data->context, radians);
}

FloatRect GraphicsContext::roundToDevicePixels(const FloatRect& frect, RoundingMode)
{
    return frect;
}

void GraphicsContext::setMiterLimit(float miter)
{
    if (paintingDisabled())
        return;
    ps_set_miter_limit(m_data->context, miter);
}

void GraphicsContext::setLineDash(const DashArray& dashes, float dashOffset)
{
    if (paintingDisabled())
        return;
    ps_set_line_dash(m_data->context, dashOffset, (float*)dashes.data(), dashes.size());
}

void GraphicsContext::setLineCap(LineCap cap)
{
    if (paintingDisabled())
        return;

    ps_context* gc = m_data->context;
    switch (cap) {
        case ButtCap:
            ps_set_line_cap(gc, LINE_CAP_BUTT);
            break;
        case RoundCap:
            ps_set_line_cap(gc, LINE_CAP_ROUND);
            break;
        case SquareCap:
            ps_set_line_cap(gc, LINE_CAP_SQUARE);
            break;
    }
}

void GraphicsContext::setLineJoin(LineJoin join)
{
    if (paintingDisabled())
        return;

    ps_context* gc = m_data->context;
    switch (join) {
        case MiterJoin:
            ps_set_line_join(gc, LINE_JOIN_MITER);
            break;
        case RoundJoin:
            ps_set_line_join(gc, LINE_JOIN_ROUND);
            break;
        case BevelJoin:
            ps_set_line_join(gc, LINE_JOIN_BEVEL);
            break;
    }
}

void GraphicsContext::drawFocusRing(const Vector<IntRect>& rects, int width, int offset, const Color& color)
{
    if (paintingDisabled())
        return;

    ps_context* gc = m_data->context;
    int radius = (width - 1) / 2;
    unsigned rectCount = rects.size();
    IntRect finalFocusRect;
    for (unsigned i = 0; i < rectCount; i++) {
        IntRect focusRect = rects[i];
        focusRect.inflate(offset);
        finalFocusRect.unite(focusRect);
    }

    ps_rect rc = { finalFocusRect.x() - 1, finalFocusRect.y() - 1,
				   finalFocusRect.width() + 1, finalFocusRect.height() + 1 };
	ps_save(gc);
#if FOCUSRING_DRAWING
    const Color col(0x14, 0x72, 0xFF);
    ps_set_line_width(gc, 2);
    setPenColor(gc, col);
	ps_path* p = ps_path_create();
	ps_path_add_rounded_rect(p, &rc, 2, 2, 2, 2, 2, 2, 2, 2);
	ps_set_path(gc, p);
	ps_stroke(gc);
	ps_path_unref(p);
#else
    setPenColor(gc, color);
	float d[] = {1, 2};
	ps_set_line_dash(gc, 0, d, 2);
    ps_rectangle(gc, &rc);
	ps_stroke(gc);
#endif
	ps_restore(gc);
}

void GraphicsContext::drawFocusRing(const Path& path, int width, int offset, const Color& color)
{
    if (paintingDisabled())
        return;

    ps_context* gc = m_data->context;
	ps_save(gc);
#if FOCUSRING_DRAWING
    const Color col(0x14, 0x72, 0xFF);
    ps_set_line_width(gc, 2);
    setPenColor(gc, col);
	ps_set_path(gc, path.platformPath());
	ps_stroke(gc);
#else
    setPenColor(gc, color);
	float d[] = {1, 2};
	ps_set_line_dash(gc, 0, d, 2);
	ps_set_path(gc, path.platformPath());
	ps_stroke(gc);
#endif
	ps_restore(gc);
}

void GraphicsContext::drawConvexPolygon(size_t numPoints, const FloatPoint* points, bool shouldAntialias)
{
    if (paintingDisabled())
        return;

    if (numPoints <= 1)
        return;

    ps_context* gc = m_data->context;

    ps_point p = { points[0].x(), points[0].y() };
    ps_move_to(gc, &p);
    for (size_t i = 1; i < numPoints; i++) {
        p.x = points[i].x(); p.y = points[i].y();
        ps_line_to(gc, &p);
    }
    ps_close_path(gc);

    bool f = false, s = false;
    if (fillColor().alpha()) {
        setBrushColor(gc, fillColor());
        ps_set_fill_rule(gc, FILL_RULE_EVEN_ODD);
        f = true;
    }

    if (strokeStyle() != NoStroke) {
        setPenColor(gc, strokeColor());
        ps_set_line_width(gc, strokeThickness());
        s = true;
    }

    ps_set_antialias(gc, shouldAntialias ? True : False);

    draw_graphic(gc, f, s);
}

void GraphicsContext::drawLine(const IntPoint& point1, const IntPoint& point2)
{
    if (paintingDisabled())
        return;

    StrokeStyle penStyle = strokeStyle();
    if (penStyle == NoStroke)
        return;

    float width = strokeThickness();
    if (width < 1)
        width = 1;

    FloatPoint p1 = point1;
    FloatPoint p2 = point2;
    bool isVerticalLine = (p1.x() == p2.x());

    adjustLineToPixelBoundaries(p1, p2, width, penStyle);
    float old_width = ps_set_line_width(m_data->context, width);

    int patWidth = 0;
    switch (penStyle) {
        case NoStroke:
        case SolidStroke:
            break;
        case DottedStroke:
            patWidth = static_cast<int>(width);
            break;
        case DashedStroke:
            patWidth = 3*static_cast<int>(width);
            break;
    }

    setPenColor (m_data->context, strokeColor());

    if (patWidth) {
        // Do a rect fill of our endpoints.  This ensures we always have the
        // appearance of being a border.  We then draw the actual dotted/dashed line.
        if (isVerticalLine) {
            fillRectSourceOver(m_data->context,
                    FloatRect(p1.x()-width/2, p1.y()-width, width, width), strokeColor());
            fillRectSourceOver(m_data->context,
                    FloatRect(p2.x()-width/2, p2.y(), width, width), strokeColor());
        } else {
            fillRectSourceOver(m_data->context,
                    FloatRect(p1.x()-width, p1.y()-width/2, width, width), strokeColor());
            fillRectSourceOver(m_data->context,
                    FloatRect(p2.x(), p2.y()-width/2, width, width), strokeColor());
        }

        // Example: 80 pixels with a width of 30 pixels.
        // Remainder is 20.  The maximum pixels of line we could paint
        // will be 50 pixels.
        int distance = (isVerticalLine ? (point2.y() - point1.y()) : (point2.x() - point1.x())) - 2*static_cast<int>(width);
        int remainder = distance%patWidth;
        int coverage = distance-remainder;
        int numSegments = coverage/patWidth;

        float patternOffset = 0;
        // Special case 1px dotted borders for speed.
        if (patWidth == 1)
            patternOffset = 1.0;
        else {
            bool evenNumberOfSegments = !(numSegments%2);
            if (remainder)
                evenNumberOfSegments = !evenNumberOfSegments;
            if (evenNumberOfSegments) {
                if (remainder) {
                    patternOffset += patWidth - remainder;
                    patternOffset += remainder/2;
                } else
                    patternOffset = patWidth/2;
            } else if (!evenNumberOfSegments) {
                if (remainder)
                    patternOffset = (patWidth - remainder)/2;
            }
        }

        float pattern[2] = { patWidth, patWidth };
        ps_set_line_dash(m_data->context, patternOffset, pattern, 2);
    }

    ps_point sp1 = {p1.x(), p1.y()};
    ps_move_to(m_data->context, &sp1);
    ps_point sp2 = {p2.x(), p2.y()};
    ps_line_to(m_data->context, &sp2);
    ps_stroke(m_data->context);

    ps_set_line_width(m_data->context, old_width);
    if (patWidth)
        ps_reset_line_dash(m_data->context);
}

void GraphicsContext::drawRect(const IntRect& r)
{
    if (paintingDisabled())
        return;

    bool f = false;
    bool s = false;
    ps_rect rect = { r.x(), r.y(), r.width(), r.height() };

    ps_rectangle(m_data->context, &rect);

    if (fillColor().alpha()) {
        f = true;
        setBrushColor(m_data->context, fillColor());
    }

    if (strokeStyle() != NoStroke) {
        s = true;
        setPenColor(m_data->context, strokeColor());
        ps_set_line_width(m_data->context, 1.0f);
    }
    draw_graphic(m_data->context, f, s);
}

void GraphicsContext::drawEllipse(const IntRect& r)
{
    if (paintingDisabled())
        return;

    bool f = false;
    bool s = false;
    ps_rect rect = { r.x(), r.y(), r.width(), r.height() };

    ps_ellipse(m_data->context, &rect);

    if (fillColor().alpha()) {
        f = true;
        setBrushColor(m_data->context, fillColor());
    }

    if (strokeStyle() != NoStroke) {
        s = true;
        setPenColor(m_data->context, strokeColor());
        ps_set_line_width(m_data->context, strokeThickness());
    }
    draw_graphic(m_data->context, f, s);
}

void GraphicsContext::drawLineForText(const FloatPoint& point, float width, bool printing)
{
    if (paintingDisabled())
        return;

    if (printing)
        return;

    StrokeStyle savedStrokeStyle = strokeStyle();
    setStrokeStyle(SolidStroke);

    IntPoint startPoint = roundedIntPoint(point);
    IntPoint endPoint = startPoint + IntSize(width, 0);
    drawLine(startPoint, endPoint);

    setStrokeStyle(savedStrokeStyle);
}

void GraphicsContext::drawLineForDocumentMarker(const FloatPoint& origin, float width, DocumentMarkerLineStyle style)
{
    notImplemented();
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
