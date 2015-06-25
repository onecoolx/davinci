/*
** GraphicContextPS.cpp: GraphicContext implements by picasso.
**
** Copyright(C) 2009 Zhang Ji Peng (onecoolx@gmail.com)
**
*/
#include "config.h"
#include <wtf/MathExtras.h>

#include "Path.h"
#include "AffineTransform.h"
#include "GraphicsContext.h"
#include "CanvasGradient.h"
#include "FloatRect.h"
#include "Font.h"
#include "FontData.h"
#include "IntRect.h"
#include "Debug.h"

namespace WebCore {

class GraphicsContextPlatformPrivate {
public:
    GraphicsContextPlatformPrivate();
    ~GraphicsContextPlatformPrivate();

    Vector<AffineTransform> stack;

    AffineTransform matrix;
    ps_context* context;
};

GraphicsContextPlatformPrivate::GraphicsContextPlatformPrivate()
    :  context(0)
{
}

GraphicsContextPlatformPrivate::~GraphicsContextPlatformPrivate()
{
}
 
GraphicsContext::GraphicsContext(ps_context* context)
    : m_common(createGraphicsContextPrivate()),
      m_data(new GraphicsContextPlatformPrivate)
{
    if (context)
        m_data->context = ps_context_ref(context);
}

GraphicsContext::~GraphicsContext()
{
    destroyGraphicsContextPrivate(m_common);
	ps_context_unref(m_data->context);
    delete m_data;
}

ps_context *GraphicsContext::platformContext() const
{
    return m_data->context;
}

void GraphicsContext::savePlatformState()
{
	ps_save(m_data->context);
    m_data->stack.append(m_data->matrix);
}

void GraphicsContext::restorePlatformState()
{
    m_data->matrix = m_data->stack.last();
    m_data->stack.removeLast();
	ps_restore(m_data->context);
}

static inline ps_color make_color(const Color& c)
{
	ps_color color;
	color.r = (double)c.red()/255;
	color.g = (double)c.green()/255;
	color.b = (double)c.blue()/255;
	color.a = (double)c.alpha()/255;
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
	(void)ps_set_composite_operator(gc, op);
}

// Draws a filled rectangle with a stroked border.
void GraphicsContext::drawRect(const IntRect& r)
{
	if (paintingDisabled())
		return;	

	bool f = false;
	bool s = false;
	ps_rect rect = {r.x(), r.y(), r.width(), r.height()};

	ps_rectangle(m_data->context, &rect);

    if (fillColor().alpha()) {
		f = true;
		setBrushColor(m_data->context, fillColor());
	}

    if (strokeStyle() != NoStroke) {
		s = true;
        setPenColor(m_data->context, strokeColor());
        ps_set_line_width(m_data->context, 1.0);
    }
	draw_graphic(m_data->context, f, s);
}

static void adjustLineToPixelBoundaries(FloatPoint& p1, FloatPoint& p2, float strokeWidth, const StrokeStyle& penStyle)
{
    // For odd widths, we add in 0.5 to the appropriate x/y so that the float arithmetic
    // works out.  For example, with a border width of 3, KHTML will pass us (y1+y2)/2, e.g.,
    // (50+53)/2 = 103/2 = 51 when we want 51.5.  It is always true that an even width gave
    // us a perfect position, but an odd width gave us a position that is off by exactly 0.5.
    if (penStyle == DottedStroke || penStyle == DashedStroke) {
        if (p1.x() == p2.x()) {
            p1.setY(p1.y() + strokeWidth);
            p2.setY(p2.y() - strokeWidth);
        }
        else {
            p1.setX(p1.x() + strokeWidth);
            p2.setX(p2.x() - strokeWidth);
        }
    }
    
    if (((int)strokeWidth)%2) {
        if (p1.x() == p2.x()) {
            // We're a vertical line.  Adjust our x.
            p1.setX(p1.x() + 0.5);
            p2.setX(p2.x() + 0.5);
        }
        else {
            // We're a horizontal line. Adjust our y.
            p1.setY(p1.y() + 0.5);
            p2.setY(p2.y() + 0.5);
        }
    }
}
// This is only used to draw borders.
void GraphicsContext::drawLine(const IntPoint& po1, const IntPoint& po2)
{
    if (paintingDisabled())
        return;	

    StrokeStyle penStyle = strokeStyle();
    if (penStyle == NoStroke)
        return;

    float width = strokeThickness();
    if (width < 1)
        width = 1;

    FloatPoint p1 = po1;
    FloatPoint p2 = po2;
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
        int distance = (isVerticalLine ? (po2.y() - po1.y()) : (po2.x() - po1.x())) - 2*static_cast<int>(width);
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

       double pattern[2] = {patWidth, patWidth};
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

// This method is only used to draw the little circles used in lists.
void GraphicsContext::drawEllipse(const IntRect& r)
{
    if (paintingDisabled())
        return;	

	bool f = false;
	bool s = false;
	ps_rect rect = {r.x(), r.y(), r.width(), r.height()};

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

void GraphicsContext::strokeArc(const IntRect& r, int startAngle, int angleSpan)
{
    if (paintingDisabled())
        return;	

    if (strokeStyle() != NoStroke) {
		float w = r.width();
		float h = r.height();
		float hRadius = w / 2;
		float vRadius = h / 2;
		float width = strokeThickness();
		if (width < 1)
			width = 1;

    	int patWidth = 0;
		switch (strokeStyle()) {
		case DottedStroke:
			patWidth = (int)(width / 2);
			break;
		case DashedStroke:
			patWidth = 3 * (int)(width / 2);
			break;
		default:
			break;
		}

        setPenColor(m_data->context, strokeColor());

    	if (patWidth) {
        	// Example: 80 pixels with a width of 30 pixels.
        	// Remainder is 20.  The maximum pixels of line we could paint
        	// will be 50 pixels.
        	int distance;
        	if (hRadius == vRadius)
            	distance = static_cast<int>((piDouble * hRadius) / 2.0);
        	else // We are elliptical and will have to estimate the distance
            	distance = static_cast<int>((piDouble * sqrtf((hRadius * hRadius + vRadius * vRadius) / 2.0)) / 2.0);

        	int remainder = distance % patWidth;
        	int coverage = distance - remainder;
        	int numSegments = coverage / patWidth;

        	float patternOffset = 0.0;
        	// Special case 1px dotted borders for speed.
        	if (patWidth == 1)
            	patternOffset = 1.0;
        	else {
            	bool evenNumberOfSegments = !(numSegments % 2);
            	if (remainder)
                	evenNumberOfSegments = !evenNumberOfSegments;
            	if (evenNumberOfSegments) {
                	if (remainder) {
                    	patternOffset += patWidth - remainder;
                    	patternOffset += remainder / 2.0;
                	} else
                    	patternOffset = patWidth / 2.0;
            	} else {
                	if (remainder)
                    	patternOffset = (patWidth - remainder) / 2.0;
            	}
        	}

       		double pattern[2] = {patWidth, patWidth};
	   		ps_set_line_dash(m_data->context, patternOffset, pattern, 2);
    	}

		ps_rect rect = {r.x(), r.y(), r.width(), r.height()};
        ps_set_line_width(m_data->context, 1.0);
		ps_tangent_arc(m_data->context, &rect, -deg2rad((double)startAngle), -deg2rad((double)angleSpan));
		ps_stroke(m_data->context);
    }

}

void GraphicsContext::drawConvexPolygon(size_t numPoints, const FloatPoint* points, bool shouldAntialias)
{
    if (paintingDisabled())
        return;

    if (numPoints <= 1)
        return;

	ps_context* gc = m_data->context;

	ps_point p = {points[0].x(), points[0].y()};
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

	draw_graphic(gc, f, s);
}

void GraphicsContext::fillRect(const FloatRect& r, const CanvasGradient* g)
{
    if (paintingDisabled())
        return;	
	ps_context* gc = m_data->context;

	ps_rect rect = {r.x(), r.y(), r.width(), r.height()};
    ps_rectangle(gc, &rect);
	ps_set_source_gradient(gc, g->getGradient());
	ps_fill(gc);
}

void GraphicsContext::fillRect(const FloatRect& r, const CanvasPattern * p)
{
    if (paintingDisabled())
        return;	
//#warning need implement
}

void GraphicsContext::fillRect(const IntRect& rect, const Color& color)
{
    if (paintingDisabled())
        return;	

	FloatRect floatrect = rect;
	fillRect(floatrect, color);
}

void GraphicsContext::fillRect(const FloatRect& r, const Color& color)
{
    if (paintingDisabled())
        return;	

    if (color.alpha()) {
        fillRectSourceOver(m_data->context, r, color);
	}
}

void GraphicsContext::clip(const IntRect& r)
{
    if (paintingDisabled())
        return;	

	ps_rect rt = {r.x(), r.y(), r.width(), r.height()};
//FIXME: need be ps_clip_rect feature when it faster..
    ps_clip_fast_rect(m_data->context, &rt);
}

void GraphicsContext::drawFocusRing(const Color& color)
{
    if (paintingDisabled())
        return;

    ps_context* gc = m_data->context;
    int radius = (focusRingWidth() - 1) / 2;
    int offset = radius + focusRingOffset();
    
    const Vector<IntRect>& rects = focusRingRects();
    unsigned rectCount = rects.size();
    IntRect finalFocusRect;
    for (unsigned i = 0; i < rectCount; i++) {
        IntRect focusRect = rects[i];
        focusRect.inflate(offset);
        finalFocusRect.unite(focusRect);
    }

    ps_rect rc = {finalFocusRect.x()-1, finalFocusRect.y()-1, 
					finalFocusRect.width()+1, finalFocusRect.height()+1};
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
#elif FOCUSRING_TV
    const Color col(0xFF, 0x00, 0x00);
    ps_set_line_width(gc, 3);
    setPenColor(gc, col);
    ps_rectangle(gc, &rc);
	ps_stroke(gc);
#else
    const Color col(0x00, 0x00, 0x00);
    setPenColor(gc, col);
	double d[] = {1, 2};
	ps_set_line_dash(gc, 0, d, 2);
    ps_rectangle(gc, &rc);
	ps_stroke(gc);
#endif
	ps_restore(gc);
}

void GraphicsContext::drawLineForText(const IntPoint& point, int width, bool printing)
{
    if (paintingDisabled())
        return;

    if (printing)
        return;
    
    StrokeStyle savedStrokeStyle = strokeStyle();
    setStrokeStyle(SolidStroke);

    IntPoint endPoint = point + IntSize(width, 0);
    drawLine(point, endPoint);
    
    setStrokeStyle(savedStrokeStyle);
}

void GraphicsContext::translate(int x, int y)
{
    if (paintingDisabled())
        return;
	ps_translate(m_data->context, x, y);
    m_data->matrix.translate((float)x, (float)y);
}


void GraphicsContext::strokeRect(const FloatRect& rect, float width) 
{
//This function paints a line of the specified width along the path of a rectangle. 
//The line surrounds the center of the path, with half of the total width on either side. 
	ps_context* gc = m_data->context;
	double oldwidth = ps_set_line_width(gc, width);
    ps_rect r = {rect.x(), rect.y(), rect.width(), rect.height()};
	ps_rectangle(gc, &r);
	ps_stroke(gc);
	(void)ps_set_line_width(gc, oldwidth);
}

void GraphicsContext::setPlatformStrokeThickness(float width) 
{
    if (paintingDisabled())
        return;
	(void)ps_set_line_width(m_data->context, width);
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

void GraphicsContext::setAlpha(float opacity) 
{
    if (paintingDisabled())
        return;	

    ps_set_alpha(m_data->context, opacity);
}

void GraphicsContext::setCompositeOperation(CompositeOperator op) 
{
    if (paintingDisabled())
        return;	

	ps_context* gc = m_data->context;
    switch (op)
    {
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
        case CompositeHighlight:
            ps_set_composite_operator(gc, COMPOSITE_PLUS);
            break;
        case CompositePlusLighter:
            ps_set_composite_operator(gc, COMPOSITE_LIGHTEN);
            break;
        default:
            ps_set_composite_operator(gc, COMPOSITE_SRC_OVER);
            break;
    }
}
void GraphicsContext::clip(const Path& path)
{
    if (paintingDisabled())
        return;	
	ps_clip_path(m_data->context, path.platformPath(), (ps_fill_rule)path.windingRule());
}

void GraphicsContext::scale(const FloatSize& size) 
{
    if (paintingDisabled())
        return;
	ps_scale(m_data->context, size.width(), size.height());
    m_data->matrix.scale (size.width(), size.height());
}

void GraphicsContext::rotate(float angle) 
{
    if (paintingDisabled())
        return;
	ps_rotate(m_data->context, angle);
    m_data->matrix.rotate (angle);
}

void GraphicsContext::setMiterLimit(float m) 
{
    if (paintingDisabled())
        return;
	ps_set_miter_limit(m_data->context, m);
}

void GraphicsContext::setPlatformFillColor(const Color& fill)
{
    if (paintingDisabled())
        return;
    setBrushColor(m_data->context, fill);
}

void GraphicsContext::setPlatformStrokeColor(const Color& color)
{
    if (paintingDisabled())
        return;
    setPenColor(m_data->context, color);
}

void GraphicsContext::strokePath(const Path& path)
{
    if (paintingDisabled())
        return;
	ps_set_path(m_data->context, path.platformPath());
	ps_stroke(m_data->context);
}

void GraphicsContext::fillPath (const Path& path)
{
    if (paintingDisabled())
        return;
	ps_set_path(m_data->context, path.platformPath());
	ps_fill(m_data->context);
}

void GraphicsContext::setPlatformFont(const Font& font)
{
    if (paintingDisabled())
        return;	
	//note: picasso will leak default font in context at here! doesn't metter.
    (void)ps_set_font(m_data->context, font.primaryFont()->m_font.hfont());
}

void GraphicsContext::fillRoundedRect(const IntRect& rc, const IntSize& topLeft, const IntSize& topRight, 
								const IntSize& bottomLeft, const IntSize& bottomRight, const Color& color)
{
    if (paintingDisabled())
        return;	

	if (color.alpha()) {
		setBrushColor(m_data->context, color);
		ps_rect r = {rc.x(), rc.y(), rc.width(), rc.height()};
		ps_rounded_rect(m_data->context, &r, topLeft.width(), topLeft.height(), topRight.width(), 
									topRight.height(), bottomLeft.width(), bottomLeft.height(), 
									bottomRight.width(), bottomRight.height());
		ps_fill(m_data->context);
	}
}

void GraphicsContext::clearRect(const FloatRect& rect) 
{
    if (paintingDisabled())
        return;	
		
	ps_save(m_data->context);
	ps_color c = {0, 0, 0, 0};
	ps_rect r = {rect.x(), rect.y(), rect.width(), rect.height()};
	ps_clip_fast_rect(m_data->context, &r);
	ps_set_source_color(m_data->context, &c);
	ps_clear(m_data->context);
	ps_restore(m_data->context);
}

void GraphicsContext::setShadow(IntSize const& size, int blur, Color const& col)
{
    if (paintingDisabled())
        return;	

	ps_color sc = make_color(col);
	ps_set_shadow(m_data->context, size.width(), size.height(), (double)blur/40);
	ps_set_shadow_color(m_data->context, &sc);
}

void GraphicsContext::clearShadow() 
{
    if (paintingDisabled())
        return;	
	ps_reset_shadow(m_data->context);
}

const AffineTransform & GraphicsContext::getMatrix(void) const
{
    return m_data->matrix;
}

void GraphicsContext::setMatrix (const AffineTransform & matrix)
{
	ps_set_matrix(m_data->context, matrix.platformTransform());
    m_data->matrix = matrix;
}

void GraphicsContext::setPlatformStrokeStyle(const StrokeStyle& style)
{
}

void GraphicsContext::setFocusRingClip(const IntRect&)
{
}

void GraphicsContext::clearFocusRingClip()
{
}

FloatRect GraphicsContext::roundToDevicePixels(const FloatRect& rect)
{
    return rect; 
}

//not implements
void GraphicsContext::setPlatformTextDrawingMode(int mode)
{
    notImplemented();
}

void GraphicsContext::clipOut(const IntRect& rect)
{
    notImplemented();
}

void GraphicsContext::clipOut(const Path&)
{
    notImplemented();
}

void GraphicsContext::addInnerRoundedRectClip(const IntRect& rect, int thickness)
{
    notImplemented()
}

void GraphicsContext::beginTransparencyLayer(float opacity) 
{ 
    notImplemented()
}

void GraphicsContext::endTransparencyLayer() 
{
    notImplemented()
}

void GraphicsContext::setURLForRect(const KURL& link, const IntRect& destRect)
{
    notImplemented();
}

void GraphicsContext::drawLineForMisspellingOrBadGrammar(const IntPoint& point, int width, bool grammar)
{
    notImplemented()
}

}

