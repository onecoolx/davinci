/*
 * WebColor.h: Color define implements by davinci.
 *
 * Copyright(C) 2016 Zhang Ji Peng (onecoolx@gmail.com)
 *
 */

#ifndef _DAVINCI_COLOR_H_
#define _DAVINCI_COLOR_H_

namespace davinci {

/**
 * \defgroup utils Utils
 * @{
 */

/* 32 bit ABGR color value, not premultiplied. The color components are always in a known order.*/
class EXPORT_API WebColor
{
public:
    WebColor() : m_color(0) { }
    WebColor(UInt32 abgr) : m_color(abgr) { }
    WebColor(UInt32 r, UInt32 g, UInt32 b, UInt32 a = 0xFF)
        : m_color((a << 24) | (b << 16) | (g << 8) | r)
    {
    }
    //8-bit type for an alpha value. 0xFF is 100% opaque, 0x00 is 100% transparent.
    //Return a WebColor value from 8 bit component values, with an implied value

    UInt32 alpha(void) const { return ((m_color) >> 24) & 0xFF; }
    UInt32 blue(void) const { return ((m_color) >> 16) & 0xFF; }
    UInt32 green(void) const { return ((m_color) >> 8) & 0xFF; }
    UInt32 red(void) const { return ((m_color) >> 0) & 0xFF; }

    void setAlpha(UInt32 a) { m_color = (m_color & 0x00FFFFFF) | (a << 24); }
    void setBlue(UInt32 b) { m_color = (m_color & 0xFF00FFFF) | (b << 16); }
    void setGreen(UInt32 g) { m_color = (m_color & 0xFFFF00FF) | (g << 8); }
    void setRed(UInt32 r) { m_color = (m_color & 0xFFFFFF00) | r; }

    enum {
        ColorBLACK     = 0xFF000000, //black
        ColorDARKGRAY  = 0xFF444444, //dark gray
        ColorGRAY      = 0xFF888888, //gray
        ColorLIGHTGRAY = 0xFFCCCCCC, //light gray
        ColorWHITE     = 0xFFFFFFFF, //white
        ColorBLUE      = 0xFFFF0000, //blue
        ColorGREEN     = 0xFF00FF00, //green
        ColorRED       = 0xFF0000FF, //red
        ColorYELLOW    = 0xFF00FFFF, //yellow
        ColorCYAN      = 0xFFFFFF00, //cyan
        ColorMAGENTA   = 0xFFFF00FF, //magenta
    };
private:
    UInt32 m_color;
};

/** @} end of utils*/

} /* namespace davinci */

#endif /*_DAVINCI_COLOR_H_*/

