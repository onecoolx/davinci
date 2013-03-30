/*
** FontPlatformDataPS.cpp: FontPlatformData implements by picasso.
**
** Copyright(C) 2009 Zhang Ji Peng (onecoolx@gmail.com)
**
*/



#include "config.h"
#include "FontPlatformData.h"

namespace WebCore {

FontPlatformData::FontPlatformData(ps_font* font, int size)
:m_font(new FontPlatformShared(font)), m_size(size)
{  
    m_font->ref();
}
    
FontPlatformData::FontPlatformData(const FontPlatformData& other)
{
    m_font = other.m_font;
    m_size = other.m_size;
    if (m_font && m_font != (FontPlatformShared*)-1)
        m_font->ref();
}

FontPlatformData& FontPlatformData::operator=(const FontPlatformData& other)
{
    if (this == &other)
        return *this;

    if (m_font && m_font != (FontPlatformShared*)-1)
        m_font->deref();

    m_font = other.m_font;
    m_size = other.m_size;
    if (m_font && m_font != (FontPlatformShared*)-1)
        m_font->ref();

    return *this;
}

FontPlatformData::~FontPlatformData()
{
    if (m_font && m_font != (FontPlatformShared*)-1)
        m_font->deref();
}

}
