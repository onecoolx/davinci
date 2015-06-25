/*
 * This file is part of the internal font implementation.
 *
 * Copyright (C) 2006 Apple Computer, Inc.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public License
 * along with this library; see the file COPYING.LIB.  If not, write to
 * the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 *
 */

#ifndef FontData_h
#define FontData_h

#include "FontPlatformData.h"
#include "GlyphPageTreeNode.h"
#include "GlyphWidthMap.h"
#include <wtf/Noncopyable.h>

#include <wtf/unicode/Unicode.h>


namespace WebCore {

class FontDescription;
class FontPlatformData;
class SharedBuffer;
class WidthMap;

enum Pitch { UnknownPitch, FixedPitch, VariablePitch };

class FontData : Noncopyable {
public:
    FontData(const FontPlatformData&, bool customFont = false, bool loading = false);
    ~FontData();

public:
    const FontPlatformData& platformData() const { return m_font; }
    FontData* smallCapsFontData(const FontDescription& fontDescription) const;

    // vertical metrics
    int ascent() const { return m_ascent; }
    int descent() const { return m_descent; }
    int lineSpacing() const { return m_lineSpacing; }
    int lineGap() const { return m_lineGap; }
    float xHeight() const { return m_xHeight; }
    unsigned unitsPerEm() const { return m_unitsPerEm; }

    float widthForGlyph(Glyph) const;
    float platformWidthForGlyph(Glyph) const;

    bool containsCharacters(const UChar* characters, int length) const;

    void determinePitch();
    Pitch pitch() const { return m_treatAsFixedPitch ? FixedPitch : VariablePitch; }

    bool isCustomFont() const { return m_isCustomFont; }
    bool isLoading() const { return m_isLoading; }

    const GlyphData& missingGlyphData() const { return m_missingGlyphData; }

private:
    void platformInit();
    void platformDestroy();
    
    void commonInit();

public:
    int m_ascent;
    int m_descent;
    int m_lineSpacing;
    int m_lineGap;
    float m_xHeight;
    unsigned m_unitsPerEm;

    FontPlatformData m_font;

    mutable GlyphWidthMap m_glyphToWidthMap;

    bool m_treatAsFixedPitch;

    bool m_isCustomFont;  // Whether or not we are custom font loaded via @font-face
    bool m_isLoading; // Whether or not this custom font is still in the act of loading.

    Glyph m_spaceGlyph;
    float m_spaceWidth;
    float m_adjustedSpaceWidth;

    GlyphData m_missingGlyphData;

    mutable FontData* m_smallCapsFontData;

};

} // namespace WebCore

#endif // FontData_h
