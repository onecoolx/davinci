/*
** PlatformWheelEvent.cpp: Wheel Event implements.
**
** Copyright(C) 2009 Zhang Ji Peng (onecoolx@gmail.com)
**
*/
#include "PlatformWheelEvent.h"
#include "SystemTime.h"

namespace WebCore {

PlatformWheelEvent::PlatformWheelEvent(int delta, IntPoint& p, unsigned flags, bool isHorizontal)
    : m_position(p)
	, m_deltaX(0)
	, m_deltaY(delta)
    , m_isAccepted(false)
    , m_shiftKey(flags & 4) // shift
    , m_ctrlKey(flags & 2) // ctrl
    , m_altKey(flags & 1) // alt
    , m_metaKey(flags & 8) // meta
	, m_isContinuous(false)
	, m_continuousDeltaX(0)
	, m_continuousDeltaY(0)
{
    m_globalPosition = p;   //FIXME: need global position!

}

} // namespace WebCore
