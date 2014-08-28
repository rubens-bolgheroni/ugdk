#ifndef UGDK_GRAPHIC_CANVAS_H_
#define UGDK_GRAPHIC_CANVAS_H_

#include <ugdk/graphic/geometry.h>
#include <ugdk/graphic/visualeffect.h>
#include <ugdk/math/vector2D.h>
#include <ugdk/structure/types.h>

#include <ugdk/internal.h>
#include <ugdk/desktop.h>
#include <ugdk/graphic.h>

#include <memory>
#include <vector>

namespace ugdk {
namespace graphic {

/**
    Binds the RenderTarget to allow rendering. Unbinds automatically on destructor.
    Creating multiple instances at the same time are supported, but the lifetime of
    the instances should act as a stack.
    TODO: example about this.

    The only valid calls on inactive instances are const-qualified methods.
*/
class Canvas {
  public:
    Canvas(RenderTarget* render_target);
    ~Canvas();

    void ChangeShaderProgram(const opengl::ShaderProgram* shader_program);

    /// Queries if this object is currently bound.
    bool IsActive() const;
    const Geometry& current_geometry() const { return geometry_stack_.back(); }
    const VisualEffect& current_visualeffect() const { return visualeffect_stack_.back(); }

    void PushAndCompose(const Geometry& geometry);
    void PushAndCompose(const VisualEffect& effect);

    void PopGeometry();
    void PopVisualEffect();

    
    void Clear(Color);
    
    // Shader variables.

    void SendUniform(const std::string& name, float t1);
    void SendUniform(const std::string& name, float t1, float t2);
    void SendUniform(const std::string& name, float t1, float t2, float t3);
    void SendUniform(const std::string& name, float t1, float t2, float t3, float t4);
    void SendUniform(const std::string& name, const TextureUnit& unit);

  private:
    void Bind();
    void Unbind();
    void SendGeometry();
    void SendEffect();

    RenderTarget* render_target_;
    std::vector<Geometry> geometry_stack_;
    std::vector<VisualEffect> visualeffect_stack_;
    const opengl::ShaderProgram* shader_program_;
    Canvas* previous_canvas_;
    Canvas* next_canvas_;
};

}  // namespace graphic
}  // namespace ugdk

#endif // UGDK_GRAPHIC_CANVAS_H_
