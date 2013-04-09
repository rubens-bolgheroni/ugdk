#ifndef HORUSEYE_FRAMEWORK_TEXT_H_
#define HORUSEYE_FRAMEWORK_TEXT_H_

#include <vector>
#include <string>
#include <ugdk/math/vector2D.h>
#include <ugdk/graphic.h>
#include <ugdk/graphic/drawable.h>
#include <freetype-gl++/texture-font.hpp>

namespace ugdk {
namespace graphic {

class Font;
class Text : public Drawable {
  public:
    Text(const std::wstring& message, freetypeglxx::TextureFont* font);
    Text(const std::vector<std::wstring>& message, freetypeglxx::TextureFont* font);
    ~Text() {}

    void SetMessage(const std::wstring& message);
    void SetMessage(const std::vector<std::wstring>& message);

    void Update(double dt);
    void Draw(const Geometry&, const VisualEffect&) const;

    virtual const ugdk::math::Vector2D& size() const;

  private:
    freetypeglxx::TextureFont* font_;
    opengl::VertexBuffer* vertex_buffer_;
    opengl::VertexBuffer* texture_buffer_;
    std::vector<std::wstring> message_;

    ugdk::math::Vector2D size_;
    double line_height_;
    std::vector<double> line_width_;
};

}  // namespace graphic
}  // namespace ugdk

#endif
