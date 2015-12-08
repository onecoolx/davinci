/*
 * PlatformKeyboardEventDavinci.cpp: PlatformKeyboardEvent implements by davinci.
 *
 * Copyright(C) 2015 Zhang Ji Peng (onecoolx@gmail.com)
 *
 */

#include "config.h"
#include "PlatformKeyboardEvent.h"

#include "NotImplemented.h"
#include "TextEncoding.h"
#include <wtf/CurrentTime.h>

namespace WebCore {

void PlatformKeyboardEvent::disambiguateKeyDownEvent(Type type, bool)
{
    ASSERT(m_type == KeyDown);
    m_type = type;

    if (type == PlatformEvent::RawKeyDown) {
        m_text = String();
        m_unmodifiedText = String();
    } else {
        m_keyIdentifier = String();
        m_windowsVirtualKeyCode = 0;
    }
}

bool PlatformKeyboardEvent::currentCapsLockState()
{
    notImplemented();
    return false;
}

void PlatformKeyboardEvent::getCurrentModifierState(bool& shiftKey, bool& ctrlKey, bool& altKey, bool& metaKey)
{
    notImplemented();
    shiftKey = false;
    ctrlKey = false;
    altKey = false;
    metaKey = false;
}

}
