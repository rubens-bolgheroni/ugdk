#include <pyramidworks/ui/button.h>

#include <ugdk/graphic/drawable.h>
#include <pyramidworks/ui/menu.h>
#include <ugdk/structure/intervalkdtree.h>

namespace pyramidworks {
namespace ui {

using namespace ugdk;

Button::Button(const ugdk::math::Vector2D& top_left, graphic::Drawable* drawable, const ButtonCallback& function)
  : function_(function)
  , top_left_(top_left)
{
    node_->set_drawable(drawable);
    node_->geometry().ChangeOffset(top_left_);
}

Button::~Button() {
    delete node_;
}

structure::Box<2> Button::GetBoundingBox() const {
    if (!node_->drawable())
        return structure::Box<2>(ugdk::math::Vector2D(0.0, 0.0), ugdk::math::Vector2D(0.0, 0.0));
    ugdk::math::Vector2D top_left = owner_->node()->geometry().offset() - node_->drawable()->hotspot();
    top_left += top_left_;
    ugdk::math::Vector2D bottom_right = top_left + node_->drawable()->size();
    return structure::Box<2>(top_left, bottom_right);
}

} // namespace ui
} // namespace pyramidworks