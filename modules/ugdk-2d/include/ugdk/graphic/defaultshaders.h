#ifndef UGDK_GRAPHIC_DEFAULTSHADERS_H_
#define UGDK_GRAPHIC_DEFAULTSHADERS_H_

#include <ugdk/graphic.h>

namespace ugdk {
namespace graphic {

opengl::ShaderProgram* CreateShader(bool light_system, bool color_text_mode);

opengl::ShaderProgram* InterfaceShader();
opengl::ShaderProgram* LightSystemShader();
opengl::ShaderProgram* InterfaceTextShader();
opengl::ShaderProgram* LightSystemTextShader();
opengl::ShaderProgram* LightShader();

}  // namespace graphic
}  // namespace ugdk

#endif