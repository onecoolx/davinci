/*
** PlatformKeyEvent.cpp: Keyboard Event implements.
**
** Copyright(C) 2009 Zhang Ji Peng (onecoolx@gmail.com)
**
*/

#include "config.h"
#include "macross.h"
#include "PlatformKeyboardEvent.h"
#include <wtf/ASCIICType.h>

namespace WebCore {

static String keyIdentifierForWindowsKeyCode(unsigned short keyCode)
{
    switch (keyCode) {
        case KEY_ALT:
            return "Alt";
		case KEY_TAB:
			return "Tab";
		case KEY_DOWN:
            return "Down";
        case KEY_END:
            return "End";
        case KEY_ENTER:
            return "Enter";
        case KEY_SPACE:
            return "Space";
		case KEY_SHIFT:
			return "Shift";
        case KEY_F1:
            return "F1";
        case KEY_F2:
            return "F2";
        case KEY_F3:
            return "F3";
        case KEY_F4:
            return "F4";
        case KEY_F5:
            return "F5";
        case KEY_F6:
            return "F6";
        case KEY_F7:
            return "F7";
        case KEY_F8:
            return "F8";
        case KEY_F9:
            return "F9";
        case KEY_F10:
            return "F11";
        case KEY_F12:
            return "F12";
        case KEY_HOME:
            return "Home";
        case KEY_INSERT:
            return "Insert";
        case KEY_LEFT:
            return "Left";
        case KEY_PAGEDOWN:
            return "PageDown";
        case KEY_PAGEUP:
            return "PageUp";
        case KEY_PAUSE:
            return "Pause";
        case KEY_RIGHT:
            return "Right";
        case KEY_UP:
            return "Up";
        case KEY_DELETE:
            return "Remove";
        default:
            return String::format("U+%04X", WTF::toASCIIUpper(keyCode));
    }
}

static String singleCharacterString(unsigned int keyCode) 
{
    UChar c = (UChar)keyCode;
    return String(&c, 1); 
}

PlatformKeyboardEvent::PlatformKeyboardEvent(bool isDown, unsigned code, unsigned flags)
    : m_text(singleCharacterString(code))
    , m_unmodifiedText(singleCharacterString(code))
    , m_keyIdentifier(keyIdentifierForWindowsKeyCode(code))
    , m_isKeyUp(!isDown)
    , m_autoRepeat((flags & 16) ? true : false)
    , m_WindowsKeyCode(code)
    , m_isKeypad(false) // FIXME: don't use keypad
    , m_shiftKey(flags & 4) // shift
    , m_ctrlKey(flags & 2) // ctrl
    , m_altKey(flags & 1) // alt
    , m_metaKey(flags & 8) // meta
{

}

}

