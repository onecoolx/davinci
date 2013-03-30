/*
** PlatformMouseEvent.cpp: Mouse Event implements.
**
** Copyright(C) 2009 Zhang Ji Peng (onecoolx@gmail.com)
**
*/
#include "config.h"
#include "macross.h"
#include "PlatformMouseEvent.h"
#include "SystemTime.h"

namespace WebCore {

PlatformMouseEvent::PlatformMouseEvent(MouseEventType type, MouseButton btn, IntPoint& p, unsigned flags, bool activatedWebView)
    : m_position(p)
	, m_button(btn)
    , m_eventType(type)
    , m_clickCount(0)
    , m_shiftKey(flags & 4) // shift
    , m_ctrlKey(flags & 2) // ctrl
    , m_altKey(flags & 1) // alt
    , m_metaKey(flags & 8) // meta
    , m_modifierFlags(flags)
    , m_activatedWebView(activatedWebView)
{
    m_timestamp = currentTime();
    m_globalPosition = p;   //FIXME: need global position!

	//FIXME: only support single click now.
	switch (type) {
		case MouseEventPressed:
		case MouseEventReleased:
			m_clickCount = 1;
			break;
		case MouseEventMoved:
			{
				if (m_button < 0)
					m_clickCount = 0;
				else
					m_clickCount = 1;
			}
			break;
		default:
			m_clickCount = 0;
			break;
	}
}

} // namespace WebCore
