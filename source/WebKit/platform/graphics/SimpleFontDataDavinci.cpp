/*
 * SimpleFontDataDavinci.cpp: SimpleFontData implements by davinci.
 *
 * Copyright(C) 2015 Zhang Ji Peng (onecoolx@gmail.com)
 *
 */

#include "config.h"
#include "SimpleFontData.h"

#include "FloatRect.h"
#include "Font.h"
#include "FontCache.h"
#include "FontDescription.h"

#include <unicode/normlzr.h>

namespace WebCore {

void SimpleFontData::platformInit()
{
}

void SimpleFontData::platformCharWidthInit()
{
}

void SimpleFontData::platformDestroy()
{
}

PassRefPtr<SimpleFontData> SimpleFontData::platformCreateScaledFontData(const FontDescription& fontDescription, float scaleFactor) const
{
	return 0;
}

bool SimpleFontData::containsCharacters(const UChar* characters, int length) const
{
    return true;
}

void SimpleFontData::determinePitch()
{
    
}

FloatRect SimpleFontData::platformBoundsForGlyph(Glyph glyph) const
{
	return FloatRect();
}

float SimpleFontData::platformWidthForGlyph(Glyph glyph) const
{
	return 0;
}

} // namespace WebCore
