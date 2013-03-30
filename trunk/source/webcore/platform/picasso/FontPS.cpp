/*
** FontPS.cpp: Font implements by picasso.
**
** Copyright(C) 2009 Zhang Ji Peng (onecoolx@gmail.com)
**
*/
#include "config.h"
#include "Font.h"
#include <wtf/MathExtras.h>

#include "CString.h"
#include "FontData.h"
#include "FontFallbackList.h"
#include "GlyphBuffer.h"
#include "GraphicsContext.h"
#include "AffineTransform.h"
#include "Debug.h"

namespace WebCore {

static inline ps_color make_color(const Color& c)
{
	ps_color color;
	color.r = ((double)c.red())/255;
	color.g = ((double)c.green())/255;
	color.b = ((double)c.blue())/255;
	color.a = ((double)c.alpha())/255;
	return color;
}

void Font::drawGlyphs(GraphicsContext* graphicsContext, const FontData* font, const GlyphBuffer& glyphBuffer,  int from, int numGlyphs, const FloatPoint& point) const
{
	/*FIXME: font css style size is zero.*/
	if (!font->m_font.size())
		return;

    ps_context* gc = graphicsContext->platformContext();
    Color pcol = graphicsContext->fillColor();
	ps_color fc = make_color(pcol);

	ps_set_text_color(gc, &fc);
	ps_set_font(gc, font->m_font.hfont());

    const GlyphBufferGlyph* glyphs = (GlyphBufferGlyph*)glyphBuffer.glyphs(from);
	ps_wide_text_out_length(gc, point.x(), point.y()-font->ascent(), glyphs, numGlyphs);
}

void Font::drawComplexText(GraphicsContext* graphicsContext, const TextRun& run, const TextStyle& style,
                                                          const FloatPoint& point, int from, int to) const
{
    drawSimpleText (graphicsContext, run, style, point, from, to);
}

float Font::floatWidthForComplexText(const TextRun& run, const TextStyle& style) const
{
    return floatWidthForSimpleText (run, style, 0);
}

FloatRect Font::selectionRectForComplexText(const TextRun& run, const TextStyle& style, const IntPoint& point, int h,
                                            int from, int to) const
{
    return selectionRectForSimpleText(run, style, point, h, from, to);
}

int Font::offsetForPositionForComplexText(const TextRun& run, const TextStyle& style, int x, bool includePartialGlyphs) const
{
    return offsetForPositionForSimpleText(run, style, x, includePartialGlyphs);
}

}
