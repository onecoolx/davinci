/*
 * DavInput.h: Input event and keymap define.
 *
 * Copyright(C) 2016 Zhang Ji Peng (onecoolx@gmail.com)
 *
 */

#ifndef _DAVINCI_INPUT_H_
#define _DAVINCI_INPUT_H_

namespace davinci {

/**
 * \defgroup event InputEvent
 * @{
 */

/**
 * \defgroup eventtype EventTypes
 * @{
 */

/**
 * \brief Modifier type.
 */
typedef enum {
	/**
	 * Alt key.
	 */
	DF_ALT	 	= 1,
	/**
	 * Ctrl key.
	 */
	DF_CTRL	 	= 2,
	/**
	 * Shift key.
	 */
	DF_SHIFT 	= 4,
	/**
	 * Meta key.
	 */
	DF_META	 	= 8,
	/**
	 * Repeat (key event only)
	 */
	DF_REPEAT 	= 16,
} ModifierType;

/**
 * \brief Mouse event type.
 * \sa KeyEventType
 */
typedef enum {
	/**
	 * Mouse up event.
	 */
	EVT_MOUSE_UP,
	/**
	 * Mouse down event.
	 */
	EVT_MOUSE_DOWN,
	/**
	 * Mouse move event.
	 */
	EVT_MOUSE_MOVE,
	/**
	 * Mouse wheel event.
	 */
	EVT_MOUSE_WHEEL,
} MouseEventType;

/**
 * \brief Mouse button type.
 * \sa VirtualKeyType
 */
typedef enum {
	/**
	 * Mouse none button.
	 */
	MOUSE_BTN_NONE	 = 0,
	/**
	 * Mouse left button.
	 */
	MOUSE_BTN_LEFT 	 = 1,
	/**
	 * Mouse right button.
	 */
	MOUSE_BTN_RIGHT  = 2,
	/**
	 * Mouse middle button.
	 */
	MOUSE_BTN_MIDDLE = 3,
	/**
	 * Mouse wheel up.
	 */
	MOUSE_WHEEL_UP	 = 4,
	/**
	 * Mouse wheel down.
	 */
	MOUSE_WHEEL_DOWN = 8,
} MouseButtonType;

/**
 * \brief Key board event type.
 * \sa MouseEventType
 */
typedef enum {
	/**
	 * Key up event.
	 */
	EVT_KEY_UP,
	/**
	 * Key down event.
	 */
	EVT_KEY_DOWN,
} KeyEventType;

/**
 * \brief Key code values for 101/102 and Microsoft extension key board.
 * \sa MouseButtonType
 */
typedef enum {
	KEY_BACK = 0x08, /**< Backspace key */
	KEY_TAB = 0x09, /**< Tab key */
	KEY_CLEAR = 0x0C, /**< Clear key */
	KEY_ENTER = 0x0D, /**< Enter key */
	KEY_SHIFT = 0x10, /**< Shift key */
	KEY_CTRL = 0x11, /**< Ctrl key */
	KEY_ALT = 0x12, /**< Alt key */
	KEY_PAUSE = 0x13, /**< Pause key */
	KEY_CAPSLOCK = 0x14, /**< Caps Lock key */
	KEY_KANA = 0x15, /**< Used with IME Kana mode */
	KEY_HANGUL = 0x15, /**< Used with IME Hangul mode */
	KEY_JUNJA = 0x17, /**< Used with IME Junja mode */
	KEY_FINAL = 0x18, /**< Used with IME Final mode */
	KEY_HANJA = 0x19, /**< Used with IME Hanja mode */
	KEY_KANJI = 0x19, /**< Used with IME Kanji mode */
	KEY_ESCAPE = 0x1B, /**< Escape key */
	KEY_CONVERT = 0x1C, /**< Used with IME Convert mode */
	KEY_NONCONVERT = 0x1D, /**< Used with IME NonConvert mode */
	KEY_ACCEPT = 0x1E, /**< Used with IME Accept mode */
	KEY_MODECHANGE = 0x1F, /**< Used with IME ModeChange mode */
	KEY_SPACE = 0x20, /**< Space key */
	KEY_PAGEUP = 0x21, /**< Page Up key */
	KEY_PAGEDOWN = 0x22, /**< Page Down key */
	KEY_END = 0x23, /**< End key */
	KEY_HOME = 0x24, /**< Home key */
	KEY_LEFT = 0x25, /**< Left Arrow key */
	KEY_UP = 0x26, /**< Up Arrow key */
	KEY_RIGHT = 0x27, /**< Right Arrow key */
	KEY_DOWN = 0x28, /**< Down Arrow key */
	KEY_SELECT = 0x29, /**< Select key */
	KEY_PRINT = 0x2A, /**< Print key */
	KEY_EXEC = 0x2B, /**< Execute key */
	KEY_PRINTSCREEN = 0x2C, /**< Print Screen key */
	KEY_INSERT = 0x2D, /**< Insert key */
	KEY_DELETE = 0x2E, /**< Delete key */
	KEY_HELP = 0x2F, /**< Help key */
	KEY_0 = 0x30, /**< 0 key */
	KEY_1 = 0x31, /**< 1 key */
	KEY_2 = 0x32, /**< 2 key */
	KEY_3 = 0x33, /**< 3 key */
	KEY_4 = 0x34, /**< 4 key */
	KEY_5 = 0x35, /**< 5 key */
	KEY_6 = 0x36, /**< 6 key */
	KEY_7 = 0x37, /**< 7 key */
	KEY_8 = 0x38, /**< 8 key */
	KEY_9 = 0x39, /**< 9 key */
	KEY_A = 0x41, /**< A key */
	KEY_B = 0x42, /**< B key */
	KEY_C = 0x43, /**< C key */
	KEY_D = 0x44, /**< D key */
	KEY_E = 0x45, /**< E key */
	KEY_F = 0x46, /**< F key */
	KEY_G = 0x47, /**< G key */
	KEY_H = 0x48, /**< H key */
	KEY_I = 0x49, /**< I key */
	KEY_J = 0x4A, /**< J key */
	KEY_K = 0x4B, /**< K key */
	KEY_L = 0x4C, /**< L key */
	KEY_M = 0x4D, /**< M key */
	KEY_N = 0x4E, /**< N key */
	KEY_O = 0x4F, /**< O key */
	KEY_P = 0x50, /**< P key */
	KEY_Q = 0x51, /**< Q key */
	KEY_R = 0x52, /**< R key */
	KEY_S = 0x53, /**< S key */
	KEY_T = 0x54, /**< T key */
	KEY_U = 0x55, /**< U key */
	KEY_V = 0x56, /**< V key */
	KEY_W = 0x57, /**< W key */
	KEY_X = 0x58, /**< X key */
	KEY_Y = 0x59, /**< Y key */
	KEY_Z = 0x5A, /**< Z key */
	KEY_LWIN = 0x5B, /**< Left Windows key (Microsoft keyboard) */
	KEY_RWIN = 0x5C, /**< Right Windows key (Microsoft keyboard) */
	KEY_APPS = 0x5D, /**< Applications key (Microsoft keyboard) */
	KEY_SLEEP = 0x5F, /**< Sleep key */
	KEY_NUMPAD0 = 0x60, /**< Numeric keypad 0 key */
	KEY_NUMPAD1 = 0x61, /**< Numeric keypad 1 key */
	KEY_NUMPAD2 = 0x62, /**< Numeric keypad 2 key */
	KEY_NUMPAD3 = 0x63, /**< Numeric keypad 3 key */
	KEY_NUMPAD4 = 0x64, /**< Numeric keypad 4 key */
	KEY_NUMPAD5 = 0x65, /**< Numeric keypad 5 key */
	KEY_NUMPAD6 = 0x66, /**< Numeric keypad 6 key */
	KEY_NUMPAD7 = 0x67, /**< Numeric keypad 7 key */
	KEY_NUMPAD8 = 0x68, /**< Numeric keypad 8 key */
	KEY_NUMPAD9 = 0x69, /**< Numeric keypad 9 key */
	KEY_MULTIPLY = 0x6A, /**< Numeric keypad Multiply key */
	KEY_ADD = 0x6B, /**< Numeric keypad Add key */
	KEY_SEPARATOR = 0x6C, /**< Numeric keypad Separator key */
	KEY_SUBTRACT = 0x6D, /**< Numeric keypad Subtract key */
	KEY_DECIMAL = 0x6E, /**< Numeric keypad Decimal key */
	KEY_DIVIDE = 0x6F, /**< Numeric keypad Divide key */
	KEY_F1 = 0x70, /**< F1 key */
	KEY_F2 = 0x71, /**< F2 key */
	KEY_F3 = 0x72, /**< F3 key */
	KEY_F4 = 0x73, /**< F4 key */
	KEY_F5 = 0x74, /**< F5 key */
	KEY_F6 = 0x75, /**< F6 key */
	KEY_F7 = 0x76, /**< F7 key */
	KEY_F8 = 0x77, /**< F8 key */
	KEY_F9 = 0x78, /**< F9 key */
	KEY_F10 = 0x79, /**< F10 key */
	KEY_F11 = 0x7A, /**< F11 key */
	KEY_F12 = 0x7B, /**< F12 key */
	KEY_F13 = 0x7C, /**< F13 key */
	KEY_F14 = 0x7D, /**< F14 key */
	KEY_F15 = 0x7E, /**< F15 key */
	KEY_F16 = 0x7F, /**< F16 key */
	KEY_F17 = 0x80, /**< F17 key */
	KEY_F18 = 0x81, /**< F18 key */
	KEY_F19 = 0x82, /**< F19 key */
	KEY_F20 = 0x83, /**< F20 key */
	KEY_F21 = 0x84, /**< F21 key */
	KEY_F22 = 0x85, /**< F22 key */
	KEY_F23 = 0x86, /**< F23 key */
	KEY_F24 = 0x87, /**< F24 key */
	KEY_NUMLOCK = 0x90, /**< Num Lock key */
	KEY_SCROLL = 0x91, /**< Scroll Lock key */
	KEY_LSHIFT = 0xA0, /**< Left Shift key (KeyState Only) */
	KEY_RSHIFT = 0xA1, /**< Right Shift key (KeyState Only) */
	KEY_LCTRL = 0xA2, /**< Left Ctrl key (KeyState Only) */
	KEY_RCTRL = 0xA3, /**< Left Ctrl key (KeyState Only) */
	KEY_LALT = 0xA4, /**< Left Alt key (KeyState Only) */
	KEY_RALT = 0xA5, /**< Left Alt key (KeyState Only) */
	KEY_BROWSER_BACK = 0xA6, /**< Browser Back key (Windows 2000/XP Only) */
	KEY_BROWSER_FORWARD = 0xA7, /**< Browser Forward key (Windows 2000/XP Only) */
	KEY_BROWSER_REFRESH = 0xA8, /**< Browser Refresh key (Windows 2000/XP Only) */
	KEY_BROWSER_STOP = 0xA9, /**< Browser Stop key (Windows 2000/XP Only) */
	KEY_BROWSER_SEARCH = 0xAA, /**< Browser Search key (Windows 2000/XP Only) */
	KEY_BROWSER_FAVORITES = 0xAB, /**< Browser Favorites key (Windows 2000/XP Only) */
	KEY_BROWSER_HOME = 0xAC, /**< Browser Home key (Windows 2000/XP Only) */
	KEY_VOLUME_MUTE = 0xAD, /**< Volume Mute key (Windows 2000/XP Only) */
	KEY_VOLUME_DOWN = 0xAE, /**< Volume Down key (Windows 2000/XP Only) */
	KEY_VOLUME_UP = 0xAF, /**< Volume Up key (Windows 2000/XP Only) */
	KEY_MEDIA_NEXT_TRACK = 0xB0, /**< Next Track key (Windows 2000/XP Only) */
	KEY_MEDIA_PREV_TRACK = 0xB1, /**< Previous Track key (Windows 2000/XP Only) */
	KEY_MEDIA_STOP = 0xB2, /**< Stop Play key (Windows 2000/XP Only) */
	KEY_MEDIA_PLAY_PAUSE = 0xB3, /**< Play/Pause key (Windows 2000/XP Only) */
	KEY_MEDIA_LAUNCH_MAIL = 0xB4, /**< Launch Mail key (Windows 2000/XP Only) */
	KEY_MEDIA_LAUNCH_MEDIA_SELECT = 0xB5, /**< Media Select key (Windows 2000/XP Only) */
	KEY_MEDIA_LAUNCH_APP1 = 0xB6, /**< Start Application 1 key (Windows 2000/XP Only) */
	KEY_MEDIA_LAUNCH_APP2 = 0xB7, /**< Start Application 2 key (Windows 2000/XP Only) */
	KEY_SEMICOLON = 0xBA, /**< Semicolon key */
	KEY_EQUAL = 0xBB, /**< Equal key */
	KEY_COMMA = 0xBC, /**< Comma key */
	KEY_MINUS = 0xBD, /**< Minus key */
	KEY_PERIOD = 0xBE, /**< Period key */
	KEY_SLASH = 0xBF, /**< Slash key */
	KEY_GRAVE = 0xC0, /**< Grave key */
	KEY_LBRACKET = 0xDB, /**< Left Bracket key */
	KEY_BACKSLASH = 0xDC, /**< Backslash key */
	KEY_RBRACKET = 0xDD, /**< Right Bracket key */
	KEY_APOSTROPHE = 0xDE, /**< Apostrophe key */
	KEY_OEM_8 = 0xDF, /**< Reserved key */
	KEY_OEM_102 = 0xE2, /**< Angle bracket or backslash on 102 keyboard */
	KEY_PROCESSKEY = 0xE5, /**< IME Process key */
	KEY_PACKET = 0xE7, /**< Windows 2000/XP used. */
	KEY_ATTN = 0xF6, /**< Attn key */
	KEY_CRSEL = 0xF7, /**< Crsel key */
	KEY_EXSEL = 0xF8, /**< Exsel key */
	KEY_EREOF = 0xF9, /**< Erase EOF key */
	KEY_PLAY = 0xFA, /**< Play key */
	KEY_ZOOM = 0xFB, /**< Zoom key */
	KEY_NONAME = 0xFC, /**< Reserved key */
	KEY_PA1 = 0xFD, /**< Pa1 key */
	KEY_OEM_CLEAR = 0xFE, /**< Clear key */
	KEY_UNKNOWN = 0,
} VirtualKeyType;

/** @} end of eventtypes*/

/**
 * \defgroup eventclass EventObject
 * @{
 */
class EXPORT_API Event
{
public:
    virtual ~Event() { }
};

class EXPORT_API TouchEvent : public Event
{
};

class EXPORT_API MouseEvent : public Event
{
};

class EXPORT_API KeyboardEvent : public Event
{
};

class EXPORT_API ContextMenuEvent : public Event
{
};

/** @} end of eventclass*/
/** @} end of event*/

} /* namespace davinci */

#endif /*_DAVINCI_INPUT_H_*/
