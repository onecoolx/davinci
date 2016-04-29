/*
 * WebSize.h: Size define implements by davinci.
 *
 * Copyright(C) 2016 Zhang Ji Peng (onecoolx@gmail.com)
 *
 */

#ifndef _DAVINCI_SIZE_H_
#define _DAVINCI_SIZE_H_

namespace davinci {

/**
 * \defgroup utils Utils
 * @{
 */

class EXPORT_API WebSize
{
public:
    WebSize()
        :m_w(0), m_h(0)
    {
    }

    WebSize(int w, int h)
        :m_w(w), m_h(h)
    {
    }

    void setSize(int w, int h)
    {
        m_w = w;
        m_h = h;
    }

    bool isEmpty(void) const
    {
        return (m_w == 0) || (m_h == 0);
    }

    int width(void) const { return m_w; }
    int height(void) const { return m_h; }

    void setWidth(int w)
    {
        if (w < 0)
            m_w = 0;
        else
            m_w = w;
    }

    void setHeight(int h)
    {
        if (h < 0)
            m_h = 0;
        else
            m_h = h;
    }
private:
    int m_w;
    int m_h;
};

/** @} end of utils*/

} /* namespace davinci */

#endif /*_DAVINCI_SIZE_H_*/
