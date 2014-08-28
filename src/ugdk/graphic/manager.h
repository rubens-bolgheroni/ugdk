#ifndef UGDK_GRAPHIC_MANAGER_H_
#define UGDK_GRAPHIC_MANAGER_H_

#include <ugdk/structure/types.h>
#include <ugdk/math/vector2D.h>

#include <ugdk/action.h>
#include <ugdk/graphic.h>
#include <ugdk/desktop.h>
#include <ugdk/internal.h>
#include <ugdk/util.h>

#include <ugdk/graphic/textureunit.h>

#include <string>
#include <bitset>
#include <functional>
#include <memory>

struct SDL_Window;
typedef void* SDL_GLContext;

namespace ugdk {
namespace graphic {

struct RenderScreen;
action::Scene* CreateLightrenderingScene(std::function<void (Canvas&)> render_light_function);

class Manager {
  public:
    Manager();
    ~Manager();

    bool Initialize(const std::weak_ptr<desktop::Window>&, const math::Vector2D& canvas_size);
    void Release();

    void AttachTo(const std::shared_ptr<desktop::Window>&);
    void ResizeScreen(const math::Vector2D& canvas_size);

#ifndef SWIG
    TextureUnit ReserveTextureUnit(const internal::GLTexture* texture = nullptr);
#endif

    class Shaders {
      public:
        enum Flag {
            USE_LIGHT_BUFFER = 0,
            IGNORE_TEXTURE_COLOR,

            NUM_FLAGS // Value generated by the compiler
        };
    
        const opengl::ShaderProgram* current_shader() const;
        
        const opengl::ShaderProgram* GetSpecificShader(const std::bitset<NUM_FLAGS>& flags) const;

        void ChangeFlag(Flag, bool);

        /// Replace the ShaderProgram UGDK uses for the given combination of flags.
        /** @arg flags A STL bitset containing the flags.
            @arg program The ShaderProgram to use. This assumes you're passing the ownership of the object.
        */
        void ReplaceShader(const std::bitset<NUM_FLAGS>& flags, opengl::ShaderProgram* program);
        
        void ReplaceShader(unsigned long flags, opengl::ShaderProgram* program) {
            ReplaceShader(std::bitset<NUM_FLAGS>(flags), program);
        }

        void ReplaceShader(const std::string& flags, opengl::ShaderProgram* program) {
            ReplaceShader(std::bitset<NUM_FLAGS>(flags), program);
        }

      private:
        Shaders();
        ~Shaders();

        opengl::ShaderProgram* shaders_[1 << NUM_FLAGS];
        std::bitset<NUM_FLAGS> flags_;

        friend class Manager;
    };

    RenderTarget* screen() const;
    RenderTexture* light_buffer() const { return light_buffer_.get(); }

    internal::GLTexture* white_texture() { return white_texture_; }
    Shaders& shaders() { return shaders_; }
    const Shaders& shaders() const { return shaders_; }
    opengl::ShaderProgram* light_shader() { return light_shader_; }

  private:
    void CreateLightBuffer(const math::Vector2D& size);
    void ReleaseTextureUnitID(int id);

    SDL_GLContext context_;
    std::unique_ptr<RenderScreen> screen_;
    std::unique_ptr<RenderTexture> light_buffer_;
    std::unique_ptr<util::IDGenerator> textureunit_ids_;
    internal::GLTexture* white_texture_;
    
    Shaders shaders_;
    opengl::ShaderProgram* light_shader_;

    friend class ::ugdk::graphic::TextureUnit;
};

}  // namespace graphic
}  // namespace ugdk

#endif // UGDK_GRAPHIC_MANAGER_H_
