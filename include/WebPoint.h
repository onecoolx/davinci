/*
 * WebPoint.h: Point define implements by davinci.
 *
 * Copyright(C) 2016 Zhang Ji Peng (onecoolx@gmail.com)
 *
 */

#ifndef _DAVINCI_POINT_H_
#define _DAVINCI_POINT_H_

namespace davinci {

/**
 * \defgroup utils Utils
 * @{
 */

class EXPORT_API WebPoint
{
public:
    WebPoint()
        :m_x(0), m_y(0)
    {
    }

    WebPoint(int x, int y)
        :m_x(x), m_y(y)
    {
    }

    void setPoint(int x, int y)
    {
        m_x = x;
        m_y = y;
    }

    int x(void) const { return m_x; }
    int y(void) const { return m_y; }

    void setX(int x) { m_x = x; }
    void setY(int y) { m_y = y; }
private:
    int m_x;
    int m_y;
};

/** @} end of utils*/

} /* namespace davinci */

#endif /*_DAVINCI_POINT_H_*/
