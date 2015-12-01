/*
 * CursorDavinci.cpp: Cursor implements by davinci.
 *
 * Copyright(C) 2015 Zhang Ji Peng (onecoolx@gmail.com)
 *
 */

#include "config.h"
#include "Cursor.h"

#include <wtf/Assertions.h>

namespace WebCore {

Cursor::Cursor(const Cursor& other)
    : m_type(other.m_type)
    , m_image(other.m_image)
    , m_hotSpot(other.m_hotSpot)
#if ENABLE(MOUSE_CURSOR_SCALE)
    , m_imageScaleFactor(other.m_imageScaleFactor)
#endif
    , m_platformCursor(other.m_platformCursor)
{
}

Cursor::~Cursor()
{
}

Cursor& Cursor::operator=(const Cursor& other)
{
    m_type = other.m_type;
    m_image = other.m_image;
    m_hotSpot = other.m_hotSpot;
#if ENABLE(MOUSE_CURSOR_SCALE)
    m_imageScaleFactor = other.m_imageScaleFactor;
#endif
    m_platformCursor = other.m_platformCursor;

    return *this;
}

void Cursor::ensurePlatformCursor() const
{
    m_platformCursor = (DS_CURSOR)m_type;
}

}
