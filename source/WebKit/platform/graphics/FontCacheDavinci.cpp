/*
 * FontCacheDavinci.cpp: FontCache implements by davinci.
 *
 * Copyright(C) 2015 Zhang Ji Peng (onecoolx@gmail.com)
 *
 */

#include "config.h"
#include "FontCache.h"

#include "Font.h"
#include "FontDescription.h"
#include "FontPlatformData.h"
#include <wtf/ListHashSet.h>
#include <wtf/StdLibExtras.h>
#include <wtf/text/StringHash.h>
#include <wtf/text/WTFString.h>

using namespace WTF;

namespace WebCore {

void FontCache::platformInit()
{
}

PassRefPtr<SimpleFontData> FontCache::systemFallbackForCharacters(const FontDescription&, const SimpleFontData* originalFontData,
                                                                  bool, const UChar* characters, int length)
{
	return 0;
}

PassRefPtr<SimpleFontData> FontCache::getLastResortFallbackFont(const FontDescription& fontDescription, ShouldRetain shouldRetain)
{
	return 0;
}

void FontCache::getTraitsInFamily(const AtomicString&, Vector<unsigned>&)
{
}

PassOwnPtr<FontPlatformData> FontCache::createFontPlatformData(const FontDescription& fontDescription, const AtomicString& familyName)
{
	return 0;
}

} // namespace WebCore
