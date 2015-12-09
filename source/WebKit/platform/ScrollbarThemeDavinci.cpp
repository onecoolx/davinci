/*
 * ScrollbarThemeDavinci.cpp: ScrollbarTheme implements by davinci.
 *
 * Copyright(C) 2015 Zhang Ji Peng (onecoolx@gmail.com)
 *
 */

#include "config.h"
#include "ScrollbarThemeDavinci.h"

namespace WebCore {

ScrollbarTheme* ScrollbarTheme::nativeTheme()
{
    static ScrollbarThemeDavinci theme;
    return &theme;
}

ScrollbarThemeDavinci::~ScrollbarThemeDavinci()
{
}

int ScrollbarThemeDavinci::scrollbarThickness(ScrollbarControlSize)
{
    return 0;
}

void ScrollbarThemeDavinci::registerScrollbar(ScrollbarThemeClient*)
{
}

void ScrollbarThemeDavinci::unregisterScrollbar(ScrollbarThemeClient*)
{
}

}

