#ifndef UGDK_GRAPHIC_VIDEOMANAGER_H_
#define UGDK_GRAPHIC_VIDEOMANAGER_H_

#include <ugdk/structure/types.h>
#include <ugdk/math/vector2D.h>

#include <ugdk/action.h>
#include <ugdk/graphic.h>

#include <string>
#include <bitset>
#include <functional>
#include <memory>

struct SDL_Window;

namespace ugdk {
namespace graphic {

action::Scene* CreateLightrenderingScene(std::function<void (Canvas&)> render_light_function);

class Manager {
  public:
    Manager(const std::weak_ptr<Canvas>&);
    ~Manager();

    bool Initialize();
    void Release();

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

    Texture* light_buffer() { return light_buffer_; }
    Texture* white_texture() { return white_texture_; }
    Shaders& shaders() { return shaders_; }
    const Shaders& shaders() const { return shaders_; }
    opengl::ShaderProgram* light_shader() { return light_shader_; }

  private:
    void CreateLightBuffer(const math::Vector2D& size);

    std::weak_ptr<Canvas> canvas_;
    Texture* light_buffer_;
    Texture* white_texture_;
    
    Shaders shaders_;
    opengl::ShaderProgram* light_shader_;
};

}  // namespace graphic
}  // namespace ugdk

#endif
