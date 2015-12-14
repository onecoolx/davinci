/*
 * FontDavinci.cpp: Font implements by davinci.
 *
 * Copyright(C) 2015 Zhang Ji Peng (onecoolx@gmail.com)
 *
 */

#include "config.h"
#include "Font.h"

#include "AffineTransform.h"
#include "FontDescription.h"
#include "FontGlyphs.h"
#include "FontSelector.h"
#include "GlyphBuffer.h"
#include "Gradient.h"
#include "GraphicsContext.h"
#include "NotImplemented.h"
#include "Pattern.h"
#include "ShadowBlur.h"
#include "TextRun.h"

namespace WebCore {

void Font::drawComplexText(GraphicsContext* ctx, const TextRun& run, const FloatPoint& point, int from, int to) const
{
}

float Font::floatWidthForComplexText(const TextRun& run, HashSet<const SimpleFontData*>*, GlyphOverflow*) const
{
	return 0;
}

int Font::offsetForPositionForComplexText(const TextRun& run, float position, bool) const
{
	return 0;
}

FloatRect Font::selectionRectForComplexText(const TextRun& run, const FloatPoint& pt, int h, int from, int to) const
{
	return FloatRect();
}

bool Font::canReturnFallbackFontsForComplexText()
{
    return false;
}

void Font::drawEmphasisMarksForComplexText(GraphicsContext* /* context */, const TextRun& /* run */, const AtomicString& /* mark */, const FloatPoint& /* point */, int /* from */, int /* to */) const
{
    notImplemented();
}

void Font::drawGlyphs(GraphicsContext* context, const SimpleFontData* fontData, const GlyphBuffer& glyphBuffer, int from, int numGlyphs, const FloatPoint& point) const
{
}


bool Font::canExpandAroundIdeographsInComplexText()
{
    return false;
}

}
