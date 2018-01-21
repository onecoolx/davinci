/*
 * FontPlatformDataDavinci.cpp: FontPlatformData implements by davinci.
 *
 * Copyright(C) 2015 Zhang Ji Peng (onecoolx@gmail.com)
 *
 */

#include "config.h"
#include "FontPlatformData.h"
#include <wtf/text/WTFString.h>

namespace WebCore {

FontPlatformData::~FontPlatformData()
{
}

void FontPlatformData::platformDataInit(const FontPlatformData& source)
{
}

const FontPlatformData& FontPlatformData::platformDataAssign(const FontPlatformData& other)
{
	return other;
}

bool FontPlatformData::platformIsEqual(const FontPlatformData& other) const
{
	return false;
}

#ifndef NDEBUG
String FontPlatformData::description() const
{
    return "iType Font Data";
}
#endif

}
