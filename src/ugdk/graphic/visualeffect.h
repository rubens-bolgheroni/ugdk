#ifndef UGDK_GRAPHIC_VISUALEFFECT_H_
#define UGDK_GRAPHIC_VISUALEFFECT_H_

#include <ugdk/base/types.h>

namespace ugdk {
namespace graphic {

class VisualEffect {
  public:
    /// Creates an identity VisualEffect;
    VisualEffect() : visible_(true) {}

    ///Creates a new VisualEffect object with the specified values. 
    /**
     * @param color The color.
     */
    VisualEffect(const ugdk::Color& color, bool _visible = true) :
        color_(color), visible_(_visible) {}

    ~VisualEffect() {}

    // Getters.
    /**@name Getters and Setters
     *@{
     */
    const ugdk::Color& color() const { return color_; }
    bool visible() const { return visible_; }

    void set_color(const ugdk::Color& _color) { color_ = _color; }
    void set_visible(bool _visible) { visible_ = _visible; }
    /**@}
     */

    void Compose(const VisualEffect& other) {
        color_.Compose(other.color_);
        visible_ = visible_ && other.visible_;
    }

    VisualEffect& operator *= (const VisualEffect& rhs) { 
        Compose(rhs);
        return *this;
    }
    
    VisualEffect operator * (const VisualEffect& rhs) const {
        VisualEffect result(*this);
        result.Compose(rhs);
        return result;
    }

  private:
    ugdk::Color color_;
    bool visible_;
};

}  // namespace graphic
}  // namespace ugdk

#endif // UGDK_GRAPHIC_VISUALEFFECT_H_
