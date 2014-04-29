#ifndef UGDK_GRAPHIC_DRAWABLE_TEXTBOX_H_
#define UGDK_GRAPHIC_DRAWABLE_TEXTBOX_H_

#include <ugdk/math/vector2D.h>
#include <ugdk/graphic.h>
#include <ugdk/graphic/drawable.h>
#include <ugdk/util/utf8.h>

#include <vector>
#include <list>
#include <string>
#include <memory>

namespace ugdk {
namespace graphic {

class TextBox : public Drawable {
  public:
    TextBox(const std::string& message, double width, Font* font);
    ~TextBox();

    enum IdentStyle {
        LEFT, CENTER, RIGHT
    };

    /// This operation is slow.
    void ChangeMessage(const std::string& message);

    void Draw(Canvas&) const override;

    void set_ident_style(IdentStyle style) { ident_style_ = style; }

    double width() const { return width_; }
    const ugdk::math::Vector2D& size() const override { return size_; }
    IdentStyle ident_style() const { return ident_style_; }

  private:
    Font* font_;
    double width_;
    std::vector< std::unique_ptr<Label> > labels_;
    IdentStyle ident_style_;

    ugdk::math::Vector2D size_;

    void splitString(const std::u32string&, std::list<std::u32string>&);
    double calculateWidth(std::u32string::const_iterator start, std::u32string::const_iterator end);
};

}  // namespace graphic
}  // namespace ugdk

#endif