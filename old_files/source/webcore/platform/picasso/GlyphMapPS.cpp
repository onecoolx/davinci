/*
** GlyphMapPS.cpp: GlyphMap implements by picasso.
**
** Copyright(C) 2009 Zhang Ji Peng (onecoolx@gmail.com)
**
*/


#include "config.h"
#include "GlyphPageTreeNode.h"
#include "FontData.h"

namespace WebCore
{

bool GlyphPage::fill(UChar* buffer, unsigned bufferLength, const FontData* fontData)
{
    // The bufferLength will be greater than the glyph page size if the buffer has Unicode supplementary characters.
    // We won't support this for now.
    if (bufferLength > GlyphPage::size)
        return false;

    for (unsigned i = 0; i < bufferLength; i++)
        setGlyphDataForIndex(i, buffer[i] , fontData);

    return true;
}

}

