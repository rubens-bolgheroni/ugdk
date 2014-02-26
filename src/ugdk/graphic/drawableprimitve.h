#ifndef UGDK_GRAPHIC_DRAWABLE_H_
#define UGDK_GRAPHIC_DRAWABLE_H_

#include <functional>

#include <ugdk/system/compatibility.h>
#include <ugdk/graphic.h>
#include <ugdk/math/vector2D.h>

namespace ugdk {
namespace graphic {

class Drawable {
  public:
    enum HookPoint {
        TOP_LEFT,       TOP,        TOP_RIGHT,
        LEFT,           CENTER,     RIGHT,
        BOTTOM_LEFT,    BOTTOM,     BOTTOM_RIGHT
    };
    virtual ~Drawable() {}

    virtual void Draw(Canvas&) const = 0;
    virtual const ugdk::math::Vector2D& size() const = 0;

    void set_draw_setup_function(const std::function<void (const Drawable*, Canvas&)> &func) {
        draw_setup_function_ = func;
    }

    void set_hotspot(const ugdk::math::Vector2D& _hotspot) { hotspot_ = _hotspot; }
    void set_hotspot(const HookPoint& hook) {
        switch(hook) {
        case TOP_LEFT    : hotspot_ = ugdk::math::Vector2D(           0.0,            0.0);  break;
        case TOP         : hotspot_ = ugdk::math::Vector2D(size().x * 0.5,            0.0);  break;
        case TOP_RIGHT   : hotspot_ = ugdk::math::Vector2D(       size().x,            0.0); break;
        case LEFT        : hotspot_ = ugdk::math::Vector2D(           0.0, size().y * 0.5);  break;
        case CENTER      : hotspot_ = size() * 0.5;                                          break;
        case RIGHT       : hotspot_ = ugdk::math::Vector2D(       size().x, size().y * 0.5); break;
        case BOTTOM_LEFT : hotspot_ = ugdk::math::Vector2D(           0.0,        size().y); break;
        case BOTTOM      : hotspot_ = ugdk::math::Vector2D(size().x * 0.5,        size().y); break;
        default          : hotspot_ = size(); /* Matches BOTTOM_RIGHT */                     break;
        }
    }

    double       width() const { return size().x; }
    double      height() const { return size().y; }
    const ugdk::math::Vector2D& hotspot() const { return hotspot_; }

  protected:
    Drawable() {}

    ugdk::math::Vector2D hotspot_;
    std::function<void (const Drawable*, Canvas&)> draw_setup_function_;
};

}  // namespace graphic
}  // namespace ugdk

#endif
