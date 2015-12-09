/*
 * ScrollbarThemeDavinci.h: ScrollbarTheme implements by davinci.
 *
 * Copyright(C) 2015 Zhang Ji Peng (onecoolx@gmail.com)
 *
 */

#ifndef ScrollbarThemeDavinci_h
#define ScrollbarThemeDavinci_h

#include "ScrollbarTheme.h"

namespace WebCore {

class ScrollbarThemeDavinci : public ScrollbarTheme {
public:
    virtual ~ScrollbarThemeDavinci();

    virtual int scrollbarThickness(ScrollbarControlSize = RegularScrollbar) OVERRIDE;

    virtual void registerScrollbar(ScrollbarThemeClient*) OVERRIDE;
    virtual void unregisterScrollbar(ScrollbarThemeClient*) OVERRIDE;
};

}
#endif // ScrollbarThemeDavinci_h

