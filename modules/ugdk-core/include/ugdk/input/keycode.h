/*
  Header adapted from SDL_keycode.h
  Original license is the following:

  Simple DirectMedia Layer
  Copyright (C) 1997-2013 Sam Lantinga <slouken@libsdl.org>

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
*/

/**
 *  Defines constants which identify keyboard keys and modifiers.
 */

#ifndef UGDK_INPUT_KEYCODE_H_
#define UGDK_INPUT_KEYCODE_H_

#include <ugdk/structure/types.h>
#include <ugdk/input/scancode.h>

namespace ugdk {
namespace input {

static const int SCANCODE_MASK = 1 << 30;
#define UGDK_SCANCODE_TO_KEYCODE(X)  (static_cast<int>(X) | SCANCODE_MASK)

/**
 *  \brief The SDL virtual key representation.
 *
 *  Values of this type are used to represent keyboard keys using the current
 *  layout of the keyboard.  These values include Unicode values representing
 *  the unmodified character that would be generated by pressing the key, or
 *  an * constant for those keys that do not generate characters.
 */
enum class Keycode
{
    UNKNOWN = 0,

    RETURN = '\r',
    ESCAPE = '\033',
    BACKSPACE = '\b',
    TAB = '\t',
    SPACE = ' ',
    EXCLAIM = '!',
    QUOTEDBL = '"',
    HASH = '#',
    PERCENT = '%',
    DOLLAR = '$',
    AMPERSAND = '&',
    QUOTE = '\'',
    LEFTPAREN = '(',
    RIGHTPAREN = ')',
    ASTERISK = '*',
    PLUS = '+',
    COMMA = ',',
    MINUS = '-',
    PERIOD = '.',
    SLASH = '/',
    ALPHANUMERIC_0 = '0',
    ALPHANUMERIC_1 = '1',
    ALPHANUMERIC_2 = '2',
    ALPHANUMERIC_3 = '3',
    ALPHANUMERIC_4 = '4',
    ALPHANUMERIC_5 = '5',
    ALPHANUMERIC_6 = '6',
    ALPHANUMERIC_7 = '7',
    ALPHANUMERIC_8 = '8',
    ALPHANUMERIC_9 = '9',
    COLON = ':',
    SEMICOLON = ';',
    LESS = '<',
    EQUALS = '=',
    GREATER = '>',
    QUESTION = '?',
    AT = '@',
    /*
       Skip uppercase letters
     */
    LEFTBRACKET = '[',
    BACKSLASH = '\\',
    RIGHTBRACKET = ']',
    CARET = '^',
    UNDERSCORE = '_',
    BACKQUOTE = '`',
    a = 'a',
    b = 'b',
    c = 'c',
    d = 'd',
    e = 'e',
    f = 'f',
    g = 'g',
    h = 'h',
    i = 'i',
    j = 'j',
    k = 'k',
    l = 'l',
    m = 'm',
    n = 'n',
    o = 'o',
    p = 'p',
    q = 'q',
    r = 'r',
    s = 's',
    t = 't',
    u = 'u',
    v = 'v',
    w = 'w',
    x = 'x',
    y = 'y',
    z = 'z',

    CAPSLOCK = UGDK_SCANCODE_TO_KEYCODE(Scancode::CAPSLOCK),

    F1 = UGDK_SCANCODE_TO_KEYCODE(Scancode::F1),
    F2 = UGDK_SCANCODE_TO_KEYCODE(Scancode::F2),
    F3 = UGDK_SCANCODE_TO_KEYCODE(Scancode::F3),
    F4 = UGDK_SCANCODE_TO_KEYCODE(Scancode::F4),
    F5 = UGDK_SCANCODE_TO_KEYCODE(Scancode::F5),
    F6 = UGDK_SCANCODE_TO_KEYCODE(Scancode::F6),
    F7 = UGDK_SCANCODE_TO_KEYCODE(Scancode::F7),
    F8 = UGDK_SCANCODE_TO_KEYCODE(Scancode::F8),
    F9 = UGDK_SCANCODE_TO_KEYCODE(Scancode::F9),
    F10 = UGDK_SCANCODE_TO_KEYCODE(Scancode::F10),
    F11 = UGDK_SCANCODE_TO_KEYCODE(Scancode::F11),
    F12 = UGDK_SCANCODE_TO_KEYCODE(Scancode::F12),

    PRINTSCREEN = UGDK_SCANCODE_TO_KEYCODE(Scancode::PRINTSCREEN),
    SCROLLLOCK = UGDK_SCANCODE_TO_KEYCODE(Scancode::SCROLLLOCK),
    PAUSE = UGDK_SCANCODE_TO_KEYCODE(Scancode::PAUSE),
    INSERT = UGDK_SCANCODE_TO_KEYCODE(Scancode::INSERT),
    HOME = UGDK_SCANCODE_TO_KEYCODE(Scancode::HOME),
    PAGEUP = UGDK_SCANCODE_TO_KEYCODE(Scancode::PAGEUP),
    DELETE = '\177',
    END = UGDK_SCANCODE_TO_KEYCODE(Scancode::END),
    PAGEDOWN = UGDK_SCANCODE_TO_KEYCODE(Scancode::PAGEDOWN),
    RIGHT = UGDK_SCANCODE_TO_KEYCODE(Scancode::RIGHT),
    LEFT = UGDK_SCANCODE_TO_KEYCODE(Scancode::LEFT),
    DOWN = UGDK_SCANCODE_TO_KEYCODE(Scancode::DOWN),
    UP = UGDK_SCANCODE_TO_KEYCODE(Scancode::UP),

    NUMLOCKCLEAR = UGDK_SCANCODE_TO_KEYCODE(Scancode::NUMLOCKCLEAR),
    NUMPAD_DIVIDE = UGDK_SCANCODE_TO_KEYCODE(Scancode::NUMPAD_DIVIDE),
    NUMPAD_MULTIPLY = UGDK_SCANCODE_TO_KEYCODE(Scancode::NUMPAD_MULTIPLY),
    NUMPAD_MINUS = UGDK_SCANCODE_TO_KEYCODE(Scancode::NUMPAD_MINUS),
    NUMPAD_PLUS = UGDK_SCANCODE_TO_KEYCODE(Scancode::NUMPAD_PLUS),
    NUMPAD_ENTER = UGDK_SCANCODE_TO_KEYCODE(Scancode::NUMPAD_ENTER),
    NUMPAD_1 = UGDK_SCANCODE_TO_KEYCODE(Scancode::NUMPAD_1),
    NUMPAD_2 = UGDK_SCANCODE_TO_KEYCODE(Scancode::NUMPAD_2),
    NUMPAD_3 = UGDK_SCANCODE_TO_KEYCODE(Scancode::NUMPAD_3),
    NUMPAD_4 = UGDK_SCANCODE_TO_KEYCODE(Scancode::NUMPAD_4),
    NUMPAD_5 = UGDK_SCANCODE_TO_KEYCODE(Scancode::NUMPAD_5),
    NUMPAD_6 = UGDK_SCANCODE_TO_KEYCODE(Scancode::NUMPAD_6),
    NUMPAD_7 = UGDK_SCANCODE_TO_KEYCODE(Scancode::NUMPAD_7),
    NUMPAD_8 = UGDK_SCANCODE_TO_KEYCODE(Scancode::NUMPAD_8),
    NUMPAD_9 = UGDK_SCANCODE_TO_KEYCODE(Scancode::NUMPAD_9),
    NUMPAD_0 = UGDK_SCANCODE_TO_KEYCODE(Scancode::NUMPAD_0),
    NUMPAD_PERIOD = UGDK_SCANCODE_TO_KEYCODE(Scancode::NUMPAD_PERIOD),

    APPLICATION = UGDK_SCANCODE_TO_KEYCODE(Scancode::APPLICATION),
    POWER = UGDK_SCANCODE_TO_KEYCODE(Scancode::POWER),
    NUMPAD_EQUALS = UGDK_SCANCODE_TO_KEYCODE(Scancode::NUMPAD_EQUALS),
    F13 = UGDK_SCANCODE_TO_KEYCODE(Scancode::F13),
    F14 = UGDK_SCANCODE_TO_KEYCODE(Scancode::F14),
    F15 = UGDK_SCANCODE_TO_KEYCODE(Scancode::F15),
    F16 = UGDK_SCANCODE_TO_KEYCODE(Scancode::F16),
    F17 = UGDK_SCANCODE_TO_KEYCODE(Scancode::F17),
    F18 = UGDK_SCANCODE_TO_KEYCODE(Scancode::F18),
    F19 = UGDK_SCANCODE_TO_KEYCODE(Scancode::F19),
    F20 = UGDK_SCANCODE_TO_KEYCODE(Scancode::F20),
    F21 = UGDK_SCANCODE_TO_KEYCODE(Scancode::F21),
    F22 = UGDK_SCANCODE_TO_KEYCODE(Scancode::F22),
    F23 = UGDK_SCANCODE_TO_KEYCODE(Scancode::F23),
    F24 = UGDK_SCANCODE_TO_KEYCODE(Scancode::F24),
    EXECUTE = UGDK_SCANCODE_TO_KEYCODE(Scancode::EXECUTE),
    HELP = UGDK_SCANCODE_TO_KEYCODE(Scancode::HELP),
    MENU = UGDK_SCANCODE_TO_KEYCODE(Scancode::MENU),
    SELECT = UGDK_SCANCODE_TO_KEYCODE(Scancode::SELECT),
    STOP = UGDK_SCANCODE_TO_KEYCODE(Scancode::STOP),
    AGAIN = UGDK_SCANCODE_TO_KEYCODE(Scancode::AGAIN),
    UNDO = UGDK_SCANCODE_TO_KEYCODE(Scancode::UNDO),
    CUT = UGDK_SCANCODE_TO_KEYCODE(Scancode::CUT),
    COPY = UGDK_SCANCODE_TO_KEYCODE(Scancode::COPY),
    PASTE = UGDK_SCANCODE_TO_KEYCODE(Scancode::PASTE),
    FIND = UGDK_SCANCODE_TO_KEYCODE(Scancode::FIND),
    MUTE = UGDK_SCANCODE_TO_KEYCODE(Scancode::MUTE),
    VOLUMEUP = UGDK_SCANCODE_TO_KEYCODE(Scancode::VOLUMEUP),
    VOLUMEDOWN = UGDK_SCANCODE_TO_KEYCODE(Scancode::VOLUMEDOWN),
    NUMPAD_COMMA = UGDK_SCANCODE_TO_KEYCODE(Scancode::NUMPAD_COMMA),
    NUMPAD_EQUALSAS400 =
        UGDK_SCANCODE_TO_KEYCODE(Scancode::NUMPAD_EQUALSAS400),

    ALTERASE = UGDK_SCANCODE_TO_KEYCODE(Scancode::ALTERASE),
    SYSREQ = UGDK_SCANCODE_TO_KEYCODE(Scancode::SYSREQ),
    CANCEL = UGDK_SCANCODE_TO_KEYCODE(Scancode::CANCEL),
    CLEAR = UGDK_SCANCODE_TO_KEYCODE(Scancode::CLEAR),
    PRIOR = UGDK_SCANCODE_TO_KEYCODE(Scancode::PRIOR),
    RETURN2 = UGDK_SCANCODE_TO_KEYCODE(Scancode::RETURN2),
    SEPARATOR = UGDK_SCANCODE_TO_KEYCODE(Scancode::SEPARATOR),
    OUT = UGDK_SCANCODE_TO_KEYCODE(Scancode::OUT),
    OPER = UGDK_SCANCODE_TO_KEYCODE(Scancode::OPER),
    CLEARAGAIN = UGDK_SCANCODE_TO_KEYCODE(Scancode::CLEARAGAIN),
    CRSEL = UGDK_SCANCODE_TO_KEYCODE(Scancode::CRSEL),
    EXSEL = UGDK_SCANCODE_TO_KEYCODE(Scancode::EXSEL),

    NUMPAD_00 = UGDK_SCANCODE_TO_KEYCODE(Scancode::NUMPAD_00),
    NUMPAD_000 = UGDK_SCANCODE_TO_KEYCODE(Scancode::NUMPAD_000),
    THOUSANDSSEPARATOR =
        UGDK_SCANCODE_TO_KEYCODE(Scancode::THOUSANDSSEPARATOR),
    DECIMALSEPARATOR =
        UGDK_SCANCODE_TO_KEYCODE(Scancode::DECIMALSEPARATOR),
    CURRENCYUNIT = UGDK_SCANCODE_TO_KEYCODE(Scancode::CURRENCYUNIT),
    CURRENCYSUBUNIT =
        UGDK_SCANCODE_TO_KEYCODE(Scancode::CURRENCYSUBUNIT),
    NUMPAD_LEFTPAREN = UGDK_SCANCODE_TO_KEYCODE(Scancode::NUMPAD_LEFTPAREN),
    NUMPAD_RIGHTPAREN = UGDK_SCANCODE_TO_KEYCODE(Scancode::NUMPAD_RIGHTPAREN),
    NUMPAD_LEFTBRACE = UGDK_SCANCODE_TO_KEYCODE(Scancode::NUMPAD_LEFTBRACE),
    NUMPAD_RIGHTBRACE = UGDK_SCANCODE_TO_KEYCODE(Scancode::NUMPAD_RIGHTBRACE),
    NUMPAD_TAB = UGDK_SCANCODE_TO_KEYCODE(Scancode::NUMPAD_TAB),
    NUMPAD_BACKSPACE = UGDK_SCANCODE_TO_KEYCODE(Scancode::NUMPAD_BACKSPACE),
    NUMPAD_A = UGDK_SCANCODE_TO_KEYCODE(Scancode::NUMPAD_A),
    NUMPAD_B = UGDK_SCANCODE_TO_KEYCODE(Scancode::NUMPAD_B),
    NUMPAD_C = UGDK_SCANCODE_TO_KEYCODE(Scancode::NUMPAD_C),
    NUMPAD_D = UGDK_SCANCODE_TO_KEYCODE(Scancode::NUMPAD_D),
    NUMPAD_E = UGDK_SCANCODE_TO_KEYCODE(Scancode::NUMPAD_E),
    NUMPAD_F = UGDK_SCANCODE_TO_KEYCODE(Scancode::NUMPAD_F),
    NUMPAD_XOR = UGDK_SCANCODE_TO_KEYCODE(Scancode::NUMPAD_XOR),
    NUMPAD_POWER = UGDK_SCANCODE_TO_KEYCODE(Scancode::NUMPAD_POWER),
    NUMPAD_PERCENT = UGDK_SCANCODE_TO_KEYCODE(Scancode::NUMPAD_PERCENT),
    NUMPAD_LESS = UGDK_SCANCODE_TO_KEYCODE(Scancode::NUMPAD_LESS),
    NUMPAD_GREATER = UGDK_SCANCODE_TO_KEYCODE(Scancode::NUMPAD_GREATER),
    NUMPAD_AMPERSAND = UGDK_SCANCODE_TO_KEYCODE(Scancode::NUMPAD_AMPERSAND),
    NUMPAD_DBLAMPERSAND =
        UGDK_SCANCODE_TO_KEYCODE(Scancode::NUMPAD_DBLAMPERSAND),
    NUMPAD_VERTICALBAR =
        UGDK_SCANCODE_TO_KEYCODE(Scancode::NUMPAD_VERTICALBAR),
    NUMPAD_DBLVERTICALBAR =
        UGDK_SCANCODE_TO_KEYCODE(Scancode::NUMPAD_DBLVERTICALBAR),
    NUMPAD_COLON = UGDK_SCANCODE_TO_KEYCODE(Scancode::NUMPAD_COLON),
    NUMPAD_HASH = UGDK_SCANCODE_TO_KEYCODE(Scancode::NUMPAD_HASH),
    NUMPAD_SPACE = UGDK_SCANCODE_TO_KEYCODE(Scancode::NUMPAD_SPACE),
    NUMPAD_AT = UGDK_SCANCODE_TO_KEYCODE(Scancode::NUMPAD_AT),
    NUMPAD_EXCLAM = UGDK_SCANCODE_TO_KEYCODE(Scancode::NUMPAD_EXCLAM),
    NUMPAD_MEMSTORE = UGDK_SCANCODE_TO_KEYCODE(Scancode::NUMPAD_MEMSTORE),
    NUMPAD_MEMRECALL = UGDK_SCANCODE_TO_KEYCODE(Scancode::NUMPAD_MEMRECALL),
    NUMPAD_MEMCLEAR = UGDK_SCANCODE_TO_KEYCODE(Scancode::NUMPAD_MEMCLEAR),
    NUMPAD_MEMADD = UGDK_SCANCODE_TO_KEYCODE(Scancode::NUMPAD_MEMADD),
    NUMPAD_MEMSUBTRACT =
        UGDK_SCANCODE_TO_KEYCODE(Scancode::NUMPAD_MEMSUBTRACT),
    NUMPAD_MEMMULTIPLY =
        UGDK_SCANCODE_TO_KEYCODE(Scancode::NUMPAD_MEMMULTIPLY),
    NUMPAD_MEMDIVIDE = UGDK_SCANCODE_TO_KEYCODE(Scancode::NUMPAD_MEMDIVIDE),
    NUMPAD_PLUSMINUS = UGDK_SCANCODE_TO_KEYCODE(Scancode::NUMPAD_PLUSMINUS),
    NUMPAD_CLEAR = UGDK_SCANCODE_TO_KEYCODE(Scancode::NUMPAD_CLEAR),
    NUMPAD_CLEARENTRY = UGDK_SCANCODE_TO_KEYCODE(Scancode::NUMPAD_CLEARENTRY),
    NUMPAD_BINARY = UGDK_SCANCODE_TO_KEYCODE(Scancode::NUMPAD_BINARY),
    NUMPAD_OCTAL = UGDK_SCANCODE_TO_KEYCODE(Scancode::NUMPAD_OCTAL),
    NUMPAD_DECIMAL = UGDK_SCANCODE_TO_KEYCODE(Scancode::NUMPAD_DECIMAL),
    NUMPAD_HEXADECIMAL =
        UGDK_SCANCODE_TO_KEYCODE(Scancode::NUMPAD_HEXADECIMAL),

    LCTRL = UGDK_SCANCODE_TO_KEYCODE(Scancode::LCTRL),
    LSHIFT = UGDK_SCANCODE_TO_KEYCODE(Scancode::LSHIFT),
    LALT = UGDK_SCANCODE_TO_KEYCODE(Scancode::LALT),
    LGUI = UGDK_SCANCODE_TO_KEYCODE(Scancode::LGUI),
    RCTRL = UGDK_SCANCODE_TO_KEYCODE(Scancode::RCTRL),
    RSHIFT = UGDK_SCANCODE_TO_KEYCODE(Scancode::RSHIFT),
    RALT = UGDK_SCANCODE_TO_KEYCODE(Scancode::RALT),
    RGUI = UGDK_SCANCODE_TO_KEYCODE(Scancode::RGUI),

    MODE = UGDK_SCANCODE_TO_KEYCODE(Scancode::MODE),

    AUDIONEXT = UGDK_SCANCODE_TO_KEYCODE(Scancode::AUDIONEXT),
    AUDIOPREV = UGDK_SCANCODE_TO_KEYCODE(Scancode::AUDIOPREV),
    AUDIOSTOP = UGDK_SCANCODE_TO_KEYCODE(Scancode::AUDIOSTOP),
    AUDIOPLAY = UGDK_SCANCODE_TO_KEYCODE(Scancode::AUDIOPLAY),
    AUDIOMUTE = UGDK_SCANCODE_TO_KEYCODE(Scancode::AUDIOMUTE),
    MEDIASELECT = UGDK_SCANCODE_TO_KEYCODE(Scancode::MEDIASELECT),
    WWW = UGDK_SCANCODE_TO_KEYCODE(Scancode::WWW),
    MAIL = UGDK_SCANCODE_TO_KEYCODE(Scancode::MAIL),
    CALCULATOR = UGDK_SCANCODE_TO_KEYCODE(Scancode::CALCULATOR),
    COMPUTER = UGDK_SCANCODE_TO_KEYCODE(Scancode::COMPUTER),
    AC_SEARCH = UGDK_SCANCODE_TO_KEYCODE(Scancode::AC_SEARCH),
    AC_HOME = UGDK_SCANCODE_TO_KEYCODE(Scancode::AC_HOME),
    AC_BACK = UGDK_SCANCODE_TO_KEYCODE(Scancode::AC_BACK),
    AC_FORWARD = UGDK_SCANCODE_TO_KEYCODE(Scancode::AC_FORWARD),
    AC_STOP = UGDK_SCANCODE_TO_KEYCODE(Scancode::AC_STOP),
    AC_REFRESH = UGDK_SCANCODE_TO_KEYCODE(Scancode::AC_REFRESH),
    AC_BOOKMARKS = UGDK_SCANCODE_TO_KEYCODE(Scancode::AC_BOOKMARKS),

    BRIGHTNESSDOWN =
        UGDK_SCANCODE_TO_KEYCODE(Scancode::BRIGHTNESSDOWN),
    BRIGHTNESSUP = UGDK_SCANCODE_TO_KEYCODE(Scancode::BRIGHTNESSUP),
    DISPLAYSWITCH = UGDK_SCANCODE_TO_KEYCODE(Scancode::DISPLAYSWITCH),
    KBDILLUMTOGGLE =
        UGDK_SCANCODE_TO_KEYCODE(Scancode::KBDILLUMTOGGLE),
    KBDILLUMDOWN = UGDK_SCANCODE_TO_KEYCODE(Scancode::KBDILLUMDOWN),
    KBDILLUMUP = UGDK_SCANCODE_TO_KEYCODE(Scancode::KBDILLUMUP),
    EJECT = UGDK_SCANCODE_TO_KEYCODE(Scancode::EJECT),
    SLEEP = UGDK_SCANCODE_TO_KEYCODE(Scancode::SLEEP)
};

Scancode CreateScancodeFromKeycode(const Keycode&);
Keycode CreateKeycodeFromScancode(const Scancode&);

#ifndef SWIG
/**
 * \brief Enumeration of valid key mods (possibly OR'd together).
 */
enum class Keymod
{
    NONE = 0x0000,

    LSHIFT = 0x0001,
    RSHIFT = 0x0002,
    SHIFT = LSHIFT | RSHIFT,

    LCTRL = 0x0040,
    RCTRL = 0x0080,
    CTRL = LCTRL | RCTRL,

    LALT = 0x0100,
    RALT = 0x0200,
    ALT = LALT | RALT,

    LGUI = 0x0400,
    RGUI = 0x0800,
    GUI = LGUI | RGUI,

    NUM = 0x1000,
    CAPS = 0x2000,
    MODE = 0x4000,
    RESERVED = 0x8000
};
inline bool operator&(const Keymod& left, const Keymod& right) {
    return (static_cast<int>(left) & static_cast<int>(right)) != 0;
}
#endif // SWIG

} // namespace input
} // namespace ugdk

#endif // UGDK_INPUT_KEYCODE_H_
