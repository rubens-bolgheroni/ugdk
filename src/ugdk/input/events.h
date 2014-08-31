#ifndef UGDK_INPUT_EVENTS_H_
#define UGDK_INPUT_EVENTS_H_

#include <ugdk/input.h>
#include <ugdk/input/keycode.h>
#include <ugdk/input/scancode.h>
#include <ugdk/input/mousebutton.h>
#include <ugdk/math/integer2D.h>

namespace ugdk {
namespace input {

struct KeyPressedEvent {
    Keycode keycode;
    Scancode scancode;
    Keymod modifiers;

    KeyPressedEvent(const Keycode& _keycode, const Scancode& _scancode,
                    const Keymod& _modifiers)
        : keycode(_keycode), scancode(_scancode), modifiers(_modifiers) {}
};
struct KeyHeldEvent {
    Keycode keycode;
    Scancode scancode;
    Keymod modifiers;
    
    KeyHeldEvent(const Keycode& _keycode, const Scancode& _scancode,
                    const Keymod& _modifiers)
        : keycode(_keycode), scancode(_scancode), modifiers(_modifiers) {}
};
struct KeyReleasedEvent {
    Keycode keycode;
    Scancode scancode;
    Keymod modifiers;
    
    KeyReleasedEvent(const Keycode& _keycode, const Scancode& _scancode,
                    const Keymod& _modifiers)
        : keycode(_keycode), scancode(_scancode), modifiers(_modifiers) {}
};

struct TextEditingEvent {
    const TextInput& input;

    TextEditingEvent(const TextInput& i) : input(i) {}
    TextEditingEvent& operator=(const TextEditingEvent&) = delete;
};

struct TextInputEvent {
    std::string text;

    TextInputEvent(const char* _text) : text(_text) {}
};

struct MouseMotionEvent {
    math::Integer2D position;
    math::Integer2D motion;
    
    MouseMotionEvent(const math::Integer2D& _position, const math::Integer2D& _motion)
        : position(_position), motion(_motion) {}
};
struct MouseButtonPressedEvent {
    math::Integer2D position;
    MouseButton button;

    MouseButtonPressedEvent(const math::Integer2D& _position, const MouseButton& _button)
        : position(_position), button(_button) {}
};
struct MouseButtonReleasedEvent {
    math::Integer2D position;
    MouseButton button;

    MouseButtonReleasedEvent(const math::Integer2D& _position, const MouseButton& _button)
        : position(_position), button(_button) {}
};
struct MouseWheelEvent {
    math::Integer2D scroll;

    MouseWheelEvent(const math::Integer2D& _scroll)
        : scroll(_scroll) {}
};

} // namespace input
} // namespace ugdk

#endif // UGDK_INPUT_EVENTS_H_
