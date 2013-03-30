/*
** Cursor.cpp: Cursor implements.
**
** Copyright(C) 2009 Zhang Ji Peng (onecoolx@gmail.com)
**
*/
#include "config.h"
#include "Cursor.h"
#include "macross.h"
#include "Debug.h"

namespace WebCore {

Cursor::Cursor(const Cursor& other)
    : m_impl(other.m_impl)
{
}

Cursor::~Cursor()
{
}

Cursor::Cursor(Image*, const IntPoint& hotspot)
{
    notImplemented()
}

Cursor& Cursor::operator=(const Cursor& other)
{
    m_impl = other.m_impl;
    return *this;
}

Cursor::Cursor(MC_CURSOR c)
    : m_impl(c)
{
}

const Cursor& pointerCursor()
{
    static Cursor c = POINTER_CURSOR;
    return c;
}

const Cursor& crossCursor()
{
    static Cursor c = CROSS_CURSOR;
    return c;
}

const Cursor& handCursor()
{
    static Cursor c = HAND_CURSOR;
    return c;
}

const Cursor& iBeamCursor()
{
    static Cursor c = IBEAM_CURSOR;
    return c;
}

const Cursor& waitCursor()
{
    static Cursor c = WAIT_CURSOR;
    return c;
}

const Cursor& helpCursor()
{
    static Cursor c = HELP_CURSOR;
    return c;
}

const Cursor& eastResizeCursor()
{
    static Cursor c = EAST_CURSOR;
    return c;
}

const Cursor& northResizeCursor()
{
    static Cursor c = NORTH_CURSOR;
    return c;
}

const Cursor& northEastResizeCursor()
{
    static Cursor c = NORTHEAST_CURSOR;
    return c;
}

const Cursor& northWestResizeCursor()
{
    static Cursor c = NORTHWEST_CURSOR;
    return c;
}

const Cursor& southResizeCursor()
{
    static Cursor c = SOUTH_CURSOR;
    return c;
}

const Cursor& southEastResizeCursor()
{
    static Cursor c = SOUTHEAST_CURSOR;
    return c;
}

const Cursor& southWestResizeCursor()
{
    static Cursor c = SOUTHWEST_CURSOR;
    return c;
}

const Cursor& westResizeCursor()
{
    static Cursor c = WEST_CURSOR;
    return c;
}

const Cursor& northSouthResizeCursor()
{
    static Cursor c = NORTHSOUTH_CURSOR;
    return c;
}

const Cursor& eastWestResizeCursor()
{
    static Cursor c = EASTWEST_CURSOR;
    return c;
}

const Cursor& northEastSouthWestResizeCursor()
{
    static Cursor c = NORTHEASTSOUTHWEST_CURSOR;
    return c;
}

const Cursor& northWestSouthEastResizeCursor()
{
    static Cursor c = NORTHWESTSOUTHEAST_CURSOR;
    return c;
}

const Cursor& columnResizeCursor()
{
    static Cursor c = COLUMN_CURSOR;
    return c;
}

const Cursor& rowResizeCursor()
{
    static Cursor c = ROW_CURSOR;
    return c;
}

const Cursor& moveCursor()
{
    static Cursor c = MOVE_CURSOR;
    return c;
}

const Cursor& cellCursor() 
{
	static Cursor c = CELL_CURSOR;
    return c;
}

const Cursor& contextMenuCursor()
{
	static Cursor c = CONTEXTMENU_CURSOR;
    return c;
}

const Cursor& verticalTextCursor()
{
	static Cursor c = VERTICALTEXT_CURSOR;
    return c;
}

const Cursor& noDropCursor()
{
	static Cursor c = NODROP_CURSOR;
    return c;
}

const Cursor& notAllowedCursor()
{
	static Cursor c = NOTALLOWED_CURSOR;
    return c;
}

const Cursor& progressCursor()
{
	static Cursor c = PROGRESS_CURSOR;
    return c;
}

const Cursor& aliasCursor()
{
	static Cursor c = ALIAS_CURSOR;
    return c;
}

const Cursor& zoomInCursor()
{
	static Cursor c = ZOOMIN_CURSOR;
    return c;
}

const Cursor& zoomOutCursor()
{
	static Cursor c = ZOOMOUT_CURSOR;
    return c;
}

const Cursor& copyCursor()
{
	static Cursor c = COPY_CURSOR;
    return c;
}

const Cursor& noneCursor()
{
	static Cursor c = NONE_CURSOR;
    return c;
}

}
