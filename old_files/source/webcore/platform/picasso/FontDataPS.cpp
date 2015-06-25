/*
** FontDataPS.cpp: FontData implements by picasso.
**
** Copyright(C) 2009 Zhang Ji Peng (onecoolx@gmail.com)
**
*/


#include "config.h"
#include "Font.h"
#include "picasso.h"
#include "FontCache.h"
#include "FloatRect.h"
#include "FontData.h"
#include "FontDescription.h"
#include <wtf/MathExtras.h>

namespace WebCore
{
extern ps_context* getGlobalContext(void);

void FontData::platformInit()
{    
	ps_font_info info;
	ps_font* f = ps_set_font(getGlobalContext(), m_font.hfont());
	ps_get_font_info(getGlobalContext(), &info);
    m_ascent = info.ascent;
    m_descent = info.descent;
    
    ps_size size;
	size = ps_get_text_extent(getGlobalContext(), "x", 1);
    m_xHeight = size.h;
    
	size = ps_get_text_extent(getGlobalContext(), " ", 1);
    m_spaceWidth = size.w;

    m_lineGap = info.leading;
    m_unitsPerEm = info.unitsEM;
    m_lineSpacing = info.ascent+info.descent+m_lineGap; 
	ps_set_font(getGlobalContext(), f);
}

void FontData::platformDestroy()
{
    delete m_smallCapsFontData;
}

FontData* FontData::smallCapsFontData(const FontDescription& fontDescription) const
{
    if (!m_smallCapsFontData) {
        int smallCapsHeight = lroundf(0.70f * fontDescription.computedSize());
        ps_font* hfont = ps_font_create_copy(m_font.hfont());
        ps_font_set_size(hfont, smallCapsHeight);
        m_smallCapsFontData = new FontData(FontPlatformData(hfont, smallCapsHeight));
    }
    return m_smallCapsFontData;
}

bool FontData::containsCharacters(const UChar* characters, int length) const
{
    return true;
}

void FontData::determinePitch()
{
    m_treatAsFixedPitch = false;
}

float FontData::platformWidthForGlyph(Glyph glyph) const
{
	/*FIXME: font css style size is zero.*/
	if (!m_font.size())
		return 0;

	ps_glyph g;
	ps_font* f = ps_set_font(getGlobalContext(), m_font.hfont());
	if (!ps_get_glyph(getGlobalContext(), (int)glyph, &g)){
		ps_set_font(getGlobalContext(), f);
		return 0;	
	}
	ps_size size = ps_glyph_get_extent(&g);
	ps_set_font(getGlobalContext(), f);
    return size.w;
}

}
