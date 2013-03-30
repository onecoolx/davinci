/*
** FontCachePS.cpp: FontCache implements by picasso.
**
** Copyright(C) 2009 Zhang Ji Peng (onecoolx@gmail.com)
**
*/

#include "config.h"
#include "DeprecatedString.h"
#include "FontCache.h"
#include "FontData.h"
#include "Font.h"
#include "Debug.h"

namespace WebCore
{

void FontCache::platformInit()
{
    notImplemented();
}

const FontData* FontCache::getFontDataForCharacters(const Font& font, const UChar* characters, int length)
{
    notImplemented();
    return 0;
}

FontPlatformData* FontCache::getSimilarFontPlatformData(const Font& font)
{
    notImplemented();
    return 0;
}

bool FontCache::fontExists(const FontDescription&, const AtomicString& family)
{
    notImplemented();
    return true;
}

FontPlatformData* FontCache::getLastResortFallbackFont(const FontDescription& fontDescription)
{
    // FIXME: Would be even better to somehow get the user's default font here.  For now we'll pick
    // the default that the user would get without changing any prefs.
    static AtomicString timesStr("Times New Roman");
    return getCachedFontPlatformData(fontDescription, timesStr);
}

FontPlatformData* FontCache::createFontPlatformData(const FontDescription& fontDescription, const AtomicString& family)
{
    ps_bool italic;
	ps_font_weight blod;

    if (fontDescription.italic())
        italic = True;
    else
        italic = False;

    if (fontDescription.bold())
        blod = FONT_WEIGHT_BOLD;
    else
        blod = FONT_WEIGHT_MEDIUM;

    ps_font* font = ps_font_create ((char*)family.deprecatedString().ascii(), CHARSET_UNICODE,
                                fontDescription.computedPixelSize(), blod, italic);

    return new FontPlatformData(font, fontDescription.computedPixelSize());
}

}
