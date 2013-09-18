#include <ugdk/input/mouse.h>

#include <ugdk/action/scene.h>
#include <ugdk/input/events.h>
#include <ugdk/internal/sdleventhandler.h>
#include <ugdk/system/engine.h>

namespace ugdk {
namespace input {

class MouseInputSDLEventHandler : public internal::SDLEventHandler {
  public:
    MouseInputSDLEventHandler(Mouse& mouse) : mouse_(mouse) {}

    bool CanHandle(const ::SDL_Event& sdlevent) const {
        return sdlevent.type == SDL_MOUSEMOTION
            || sdlevent.type == SDL_MOUSEBUTTONDOWN
            || sdlevent.type == SDL_MOUSEBUTTONUP
            || sdlevent.type == SDL_MOUSEWHEEL;
    }

    void Handle(const ::SDL_Event& sdlevent) const {
        if(sdlevent.type == SDL_MOUSEMOTION)
            MouseMotionHandler(sdlevent);
        else if(sdlevent.type == SDL_MOUSEBUTTONDOWN)
            MouseButtonDownHandler(sdlevent);
        else if(sdlevent.type == SDL_MOUSEBUTTONUP)
            MouseButtonUpHandler(sdlevent);
        else if(sdlevent.type == SDL_MOUSEWHEEL)
            MouseWheelHandler(sdlevent);
        else
            assert(false);
    }

    void MouseMotionHandler(const ::SDL_Event& sdlevent) const {
        mouse_.position_.x = sdlevent.motion.x;
        mouse_.position_.y = sdlevent.motion.y;
        system::CurrentScene()->event_handler().ScheduleEvent(MouseMotionEvent(
            math::Integer2D(sdlevent.motion.xrel, sdlevent.motion.yrel)
        ));
    }

    void MouseButtonDownHandler(const ::SDL_Event& sdlevent) const {
        MouseButton button = static_cast<MouseButton>(sdlevent.button.button-1);
        system::CurrentScene()->event_handler().ScheduleEvent(MouseButtonPressedEvent(button));
        mouse_.state_.insert(button);
    }

    void MouseButtonUpHandler(const ::SDL_Event& sdlevent) const {
        MouseButton button = static_cast<MouseButton>(sdlevent.button.button-1);
        system::CurrentScene()->event_handler().ScheduleEvent(MouseButtonReleasedEvent(button));
        mouse_.state_.erase(button);
    }

    void MouseWheelHandler(const ::SDL_Event& sdlevent) const {
        system::CurrentScene()->event_handler().ScheduleEvent(MouseWheelEvent(
            math::Integer2D(sdlevent.wheel.x, sdlevent.wheel.y)
        ));
    }


  private:
    void operator=(const MouseInputSDLEventHandler&);

    Mouse& mouse_;
};

bool Mouse::IsDown(const MouseButton& button) const {
    return state_.count(button) > 0;
}
bool Mouse::IsUp(const MouseButton& button) const {
    return state_.count(button) == 0;
}

bool Mouse::IsPressed(const MouseButton& button) const {
    return IsDown(button) && state_previous_.count(button) == 0;
}
bool Mouse::IsReleased(const MouseButton& button) const {
    return IsUp(button) && state_previous_.count(button) > 0;
}

Mouse::Mouse() : event_handler_(new MouseInputSDLEventHandler(*this)) {}

Mouse::~Mouse() {}

void Mouse::Update() {
    state_previous_ = state_;
}

const internal::SDLEventHandler* Mouse::event_handler() {
    return event_handler_.get();
}

} // namespace input
} // namespace ugdk