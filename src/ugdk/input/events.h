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

struct MouseMotionEvent {
    math::Integer2D motion;
    
    MouseMotionEvent(const math::Integer2D& _motion)
        : motion(_motion) {}
};
struct MouseButtonPressedEvent {
    MouseButton button;

    MouseButtonPressedEvent(const MouseButton& _button)
        : button(_button) {}
};
struct MouseButtonReleasedEvent {
    MouseButton button;

    MouseButtonReleasedEvent(const MouseButton& _button)
        : button(_button) {}
};
struct MouseWheelEvent {
    math::Integer2D scroll;

    MouseWheelEvent(const math::Integer2D& _scroll)
        : scroll(_scroll) {}
};

} // namespace input
} // namespace ugdk

#endif // UGDK_INPUT_EVENTS_H_