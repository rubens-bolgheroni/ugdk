#include <ugdk/graphic/primitive.h>

#include <ugdk/graphic/primitivecontroller.h>

namespace ugdk {
namespace graphic {

Primitive::Primitive(const graphic::GLTexture* texture, const std::shared_ptr<VertexData>& data)
    : texture_(texture)
    , vertexdata_(data)
    , controller_(nullptr)
    , shader_program_(nullptr)
{}

Primitive::~Primitive() {}

void Primitive::set_controller(std::unique_ptr<PrimitiveController>&& controller) {
    controller_ = std::move(controller);
    controller_->set_owner(this);
}

#ifdef _MSC_VER
#if _MSC_VER <= 1800
Primitive::Primitive(Primitive&& primitive) {
    *this = std::move(primitive);
}

Primitive& Primitive::operator=(Primitive&& primitive) {
    texture_ = primitive.texture_;
    vertexdata_ = primitive.vertexdata_;
    drawfunction_ = primitive.drawfunction_;
    controller_ = std::move(primitive.controller_);
    visual_effect_ = primitive.visual_effect_;
    shader_program_ = primitive.shader_program_;
    return *this;
}
#endif
#endif

}  // namespace graphic
}  // namespace ugdk
