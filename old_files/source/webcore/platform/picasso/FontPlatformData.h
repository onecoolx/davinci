/*
** FontPlatformData.h: FontPlatformData implements by picasso.
**
** Copyright(C) 2009 Zhang Ji Peng (onecoolx@gmail.com)
**
*/


#ifndef FontPlatformData_H
#define FontPlatformData_H

#include "StringImpl.h"
#include "picasso.h"

namespace WebCore {

class FontDescription;

class FontPlatformShared : public Shared<FontPlatformShared>
{
public:
    FontPlatformShared(ps_font* font)
        :m_font(font)
    {
    }
    ~FontPlatformShared()
    {
        ps_font_unref(m_font);
    }

    ps_font* font(void) {return m_font;}
private:
    ps_font* m_font;
};

class FontPlatformData
{
public:
    class Deleted {};

    // Used for deleted values in the font cache's hash tables.
    FontPlatformData(Deleted)
    : m_font((FontPlatformShared*)-1), m_size(0)
    {}

    FontPlatformData()
    : m_font(0), m_size(0)
    {}

    FontPlatformData(ps_font*, int);
    ~FontPlatformData();

    ps_font* hfont() const { return m_font->font(); }

    int size() const { return m_size; }

    unsigned hash() const
    { 
        return StringImpl::computeHash((UChar*)(&m_font), sizeof(FontPlatformShared *) / sizeof(UChar));
    }

    bool operator==(const FontPlatformData& other) const
    { 
        if (!m_font && !other.m_font)
            return true;

        if(!other.m_font || (other.m_font == (FontPlatformShared*)-1))
            return false;

        return ((m_font->font() == other.hfont()) && (m_size == other.size()));
    }

    FontPlatformData(const FontPlatformData&);
    FontPlatformData& operator=(const FontPlatformData&);
private:
    FontPlatformShared *m_font;
    int m_size;
};

}

#endif

