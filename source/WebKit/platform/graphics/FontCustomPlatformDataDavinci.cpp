/*
 * FontCustomPlatformDataDavinci.cpp: FontCustomPlatformData implements by davinci.
 *
 * Copyright(C) 2015 Zhang Ji Peng (onecoolx@gmail.com)
 *
 */

#include "config.h"
#include "FontCustomPlatformData.h"

#include "FontPlatformData.h"
#include "SharedBuffer.h"

namespace WebCore {

FontCustomPlatformData::FontCustomPlatformData(const char* fontName, PassRefPtr<SharedBuffer> buffer)
    : m_buffer(buffer)
{
}

FontCustomPlatformData::~FontCustomPlatformData()
{
}

FontPlatformData FontCustomPlatformData::fontPlatformData(int size, bool syntheticBold, bool syntheticItalic, FontOrientation orientation, FontWidthVariant widthVariant, FontRenderingMode)
{
    //return FontPlatformData(m_fontName, size, syntheticBold, syntheticItalic, orientation, widthVariant);
}

bool FontCustomPlatformData::supportsFormat(const String& format)
{
    return true;
}

FontCustomPlatformData* createFontCustomPlatformData(SharedBuffer* buffer)
{
#if 0
    ASSERT_ARG(buffer, buffer);

#if USE(OPENTYPE_SANITIZER)
    OpenTypeSanitizer sanitizer(buffer);
    RefPtr<SharedBuffer> transcodeBuffer = sanitizer.sanitize();
    if (!transcodeBuffer)
        return 0; // validation failed.
    buffer = transcodeBuffer.get();
#endif

    FILECHAR name[MAX_FONT_NAME_LEN+1];
    memset(name, 0, MAX_FONT_NAME_LEN+1);
    if (FS_load_font(BlackBerry::Platform::Graphics::getIType(), 0, const_cast<FS_BYTE*>(reinterpret_cast<const FS_BYTE*>(buffer->data())), 0, MAX_FONT_NAME_LEN, name) != SUCCESS)
        return 0;

    return new FontCustomPlatformData(name, buffer);
#endif
}

}
