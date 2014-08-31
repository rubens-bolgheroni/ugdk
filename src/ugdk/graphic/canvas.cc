#include <ugdk/graphic/canvas.h>

#include <ugdk/graphic/exceptions.h>
#include <ugdk/graphic/module.h>
#include <ugdk/graphic/rendertarget.h>
#include <ugdk/graphic/textureunit.h>
#include <ugdk/graphic/vertexdata.h>
#include <ugdk/graphic/opengl/shaderprogram.h>
#include <ugdk/graphic/opengl/vertexbuffer.h>
#include <ugdk/internal/gltexture.h>

namespace ugdk {
namespace graphic {

namespace {
Canvas* ACTIVE_CANVAS = nullptr;
}

Canvas::Canvas(RenderTarget* render_target)
    : render_target_(render_target)
    , shader_program_(nullptr)
    , previous_canvas_(nullptr)
    , next_canvas_(nullptr)
{
    geometry_stack_.emplace_back(render_target_->projection_matrix());
    visualeffect_stack_.emplace_back();

    if (ACTIVE_CANVAS) {
        previous_canvas_ = ACTIVE_CANVAS;
        previous_canvas_->Unbind();
        previous_canvas_->next_canvas_ = this;
    }
    ACTIVE_CANVAS = this;
    Bind();
}

Canvas::~Canvas() {
    if (IsActive()) {
        Unbind();
        if (next_canvas_)
            ACTIVE_CANVAS = next_canvas_;
        else
            ACTIVE_CANVAS = previous_canvas_;

        if (ACTIVE_CANVAS)
            ACTIVE_CANVAS->Bind();
    }

    if (next_canvas_)
        next_canvas_->previous_canvas_ = previous_canvas_;
    if (previous_canvas_)
        previous_canvas_->next_canvas_ = next_canvas_;
}

void Canvas::ChangeShaderProgram(const opengl::ShaderProgram* shader_program) {
    shader_program_ = shader_program;
    glUseProgram(shader_program_->id());
}

bool Canvas::IsActive() const {
    return ACTIVE_CANVAS == this;
}

void Canvas::PushAndCompose(const Geometry& geometry) {
    geometry_stack_.reserve(geometry_stack_.size() + 1);
    geometry_stack_.emplace_back(geometry_stack_.back());
    geometry_stack_.back().Compose(geometry);
    if (shader_program_)
        SendGeometry();
}

void Canvas::PushAndCompose(const VisualEffect& effect) {
    visualeffect_stack_.reserve(visualeffect_stack_.size() + 1);
    visualeffect_stack_.emplace_back(visualeffect_stack_.back());
    visualeffect_stack_.back().Compose(effect);
    if (shader_program_)
        SendEffect();
}

void Canvas::PopGeometry() {
    AssertCondition<InvalidOperation>(geometry_stack_.size() > 1, "Can only pop a Geometry after pushing at least one.");
    geometry_stack_.pop_back();
}

void Canvas::PopVisualEffect() {
    AssertCondition<InvalidOperation>(visualeffect_stack_.size() > 1, "Can only pop a VisualEffect after pushing at least one.");
    visualeffect_stack_.pop_back();
}

void Canvas::Clear(Color color) {
    render_target_->Clear(color);
}

void Canvas::SendUniform(const std::string& name, float t1) {
    glUniform1f(shader_program_->UniformLocation(name), t1);
    internal::AssertNoOpenGLError();
}
void Canvas::SendUniform(const std::string& name, float t1, float t2) {
    glUniform2f(shader_program_->UniformLocation(name), t1, t2);
    internal::AssertNoOpenGLError();
}
void Canvas::SendUniform(const std::string& name, float t1, float t2, float t3) {
    glUniform3f(shader_program_->UniformLocation(name), t1, t2, t3);
    internal::AssertNoOpenGLError();
}
void Canvas::SendUniform(const std::string& name, float t1, float t2, float t3, float t4) {
    glUniform4f(shader_program_->UniformLocation(name), t1, t2, t3, t4);
    internal::AssertNoOpenGLError();
}

void Canvas::SendUniform(const std::string& name, const TextureUnit& unit) {
    glUniform1i(shader_program_->UniformLocation(name), unit.id());
}

void Canvas::Bind() {
    render_target_->Bind();
    if (shader_program_)
        glUseProgram(shader_program_->id());
}

void Canvas::Unbind() {
    render_target_->Unbind();
    glUseProgram(0);
}

void Canvas::SendGeometry() {
    glUniformMatrix4fv(shader_program_->UniformLocation("geometry_matrix"), 1, GL_FALSE, &current_geometry().AsMat4()[0][0]);
    internal::AssertNoOpenGLError();
}
     
void Canvas::SendEffect() {
    const Color& c = current_visualeffect().color();
    glUniform4f(shader_program_->UniformLocation("effect_color"), c.r, c.g, c.b, c.a);
    internal::AssertNoOpenGLError();
}

void Canvas::SendVertexData(const VertexData* data, VertexType type, size_t offset, int size) {
    opengl::VertexBuffer::Bind bind(*data->buffer().get());

    unsigned int location = manager()->LocationForVertexType(type);
    glEnableVertexAttribArray(location);

    glVertexAttribPointer(
        location,            // location
        size,                // size
        GL_FLOAT,            // data type
        GL_FALSE,            // normalized?
        data->vertex_size(), // ammount of bytes to offset for each element. 0 means size*sizeof(type)
        data->buffer()->getPointer(offset) // array buffer offset
    );
    internal::AssertNoOpenGLError();
}

}  // namespace graphic
}  // namespace ugdk
