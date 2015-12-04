/*
 * Copyright (C) 2015 Zhang Ji Peng <onecoolx@gmail.com>. All rights reserved.
 */

#ifndef FontCustomPlatformData_h
#define FontCustomPlatformData_h

#include "FontOrientation.h"
#include "FontRenderingMode.h"
#include "FontWidthVariant.h"
#include <wtf/Noncopyable.h>
#include <wtf/text/WTFString.h>

namespace WebCore {

class FontPlatformData;
class MonotypeFont;
class SharedBuffer;

struct FontCustomPlatformData {
    WTF_MAKE_NONCOPYABLE(FontCustomPlatformData);
public:
    FontCustomPlatformData(const char* fontName, PassRefPtr<SharedBuffer>);
    ~FontCustomPlatformData();

    FontPlatformData fontPlatformData(int size, bool syntheticBold, bool syntheticItalic, FontOrientation = Horizontal,
        FontWidthVariant = RegularWidth, FontRenderingMode = NormalRenderingMode);

    static bool supportsFormat(const String&);

    RefPtr<SharedBuffer> m_buffer;
};

FontCustomPlatformData* createFontCustomPlatformData(SharedBuffer*);

} // namespace WebCore

#endif // FontCustomPlatformData_h
