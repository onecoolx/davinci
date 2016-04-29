/*
 * WebRect.h: Rectangle define implements by davinci.
 *
 * Copyright(C) 2016 Zhang Ji Peng (onecoolx@gmail.com)
 *
 */

#ifndef _DAVINCI_RECT_H_
#define _DAVINCI_RECT_H_

namespace davinci {

/**
 * \defgroup utils Utils
 * @{
 */

class EXPORT_API WebRect
{
public:
    WebRect()
    {
    }

    WebRect(int w, int h)
        : m_size(w, h)
    {
    }

    WebRect(int x, int y, int w, int h)
        : m_origin(x, y)
        , m_size(w, h)
    {
    }

    void setRect(int x, int y, int w, int h)
    {
        m_origin.setPoint(x, y);
        m_size.setSize(w, h);
    }

    void setX(int x) { m_origin.setX(x); }
    void setY(int y) { m_origin.setY(y); }
    void setWidth(int w) { m_size.setWidth(w); }
    void setHeight(int h) { m_size.setHeight(h); }

    int x(void) const { return m_origin.x(); }
    int y(void) const { return m_origin.y(); }
    int width(void) const { return m_size.width(); }
    int height(void) const { return m_size.height(); }
    int left(void) const { return x(); }
    int top(void) const { return y(); }
    int right(void) const { return x() + width(); }
    int bottom(void) const { return y() + height(); }

    bool isEmpty(void) const { return m_size.isEmpty(); }
private:
    WebPoint m_origin;
    WebSize m_size;
};

/** @} end of utils*/

} /* namespace davinci */

#endif /*_DAVINCI_RECT_H_*/
