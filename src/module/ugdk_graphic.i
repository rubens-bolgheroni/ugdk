
%module ugdk_graphic

%include <module/util_ugdk.swig>

%include "std_string.i"
%include "std_vector.i"
%include "std_map.i"

#define final

%{

#include <ugdk/graphic/geometry.h>
#include <ugdk/graphic/visualeffect.h>
#include <ugdk/graphic/drawable.h>
#include <ugdk/graphic/image.h>
#include <ugdk/graphic/light.h>
#include <ugdk/graphic/node.h>
#include <ugdk/graphic/drawmode.h>
#include <ugdk/graphic/canvas.h>
#include <ugdk/graphic/textureatlas.h>
#include <ugdk/graphic/textureunit.h>
#include <ugdk/graphic/rendertarget.h>
#include <ugdk/graphic/rendertexture.h>
#include <ugdk/graphic/manager.h>
#include <ugdk/graphic/module.h>
#include <ugdk/graphic/vertexdata.h>
#include <ugdk/graphic/primitive.h>
#include <ugdk/graphic/text/font.h>
#include <ugdk/graphic/text/textmanager.h>

%}

%import(module="ugdk_math") <ugdk/math/vector2D.h>
%import(module="ugdk_math") <ugdk/math/frame.h>
%import(module="ugdk_desktop") <ugdk/desktop.h>

%ignore ugdk::graphic::Font::GetLetterSize(wchar_t letter);
%ignore ugdk::graphic::SpritesheetData::frames() const;

%newobject ugdk::graphic::Font::GetLetterSize(wchar_t letter);
%newobject ugdk::graphic::Geometry::Compose(const Geometry* mod1, const Geometry* mod2);
%newobject ugdk::graphic::Geometry::Copy(const Geometry* mod2);
%newobject ugdk::graphic::TextManager::GetText(const std::wstring& text);
%newobject ugdk::graphic::TextManager::GetText(const std::wstring& text, const std::string& font, int width = -1);
%newobject ugdk::graphic::TextManager::GetTextFromFile(const std:: string& path);
%newobject ugdk::graphic::TextManager::GetTextFromFile(const std:: string& path, const std::string& font, int width = -1);

%rename(ComposeNew) ugdk::graphic::Geometry::Compose(const Geometry* mod1, const Geometry* mod2);
%rename(GetTextWithFont) ugdk::graphic::TextManager::GetText(const std::wstring& text, const std::string& font, int width = -1);

%include <ugdk/graphic.h>

%include <ugdk/graphic/geometry.h>
%include <ugdk/graphic/visualeffect.h>
%include <ugdk/graphic/drawable.h>

%import(module="ugdk_system") <ugdk/structure/types.h>
%import(module="ugdk_action") <ugdk/action.h>
%import(module="ugdk_internal") <ugdk/internal.h>
%import(module="ugdk_drawable") <ugdk/graphic/text/textbox.h> //this needs to go after the include drawable.h

%include <ugdk/graphic/drawmode.h>
%include <ugdk/graphic/canvas.h>
%include <ugdk/graphic/image.h>
%include <ugdk/graphic/light.h>
enable_disown(ugdk::graphic::Node* new_child)
enable_disown(ugdk::graphic::Drawable* drawable)
%include <ugdk/graphic/node.h>
disable_disown(ugdk::graphic::Drawable* drawable)
disable_disown(ugdk::graphic::Node* new_child)
%include <ugdk/graphic/textureatlas.h>
%include <ugdk/graphic/textureunit.h>
%include <ugdk/graphic/rendertarget.h>
%include <ugdk/graphic/rendertexture.h>

%include <ugdk/graphic/vertexdata.h>
%include <ugdk/graphic/primitive.h>

%include <ugdk/graphic/text/font.h>
%include <ugdk/graphic/text/textmanager.h>

%include <ugdk/graphic/manager.h>
%include <ugdk/graphic/module.h>

namespace ugdk {
namespace graphic {
	export_class(DrawMode)
    export_class(Canvas)
    export_class(Drawable)
    export_class(Image)
    export_class(Font)
    export_class(Light)
    export_class(Geometry)
    export_class(VisualEffect)
    export_class(Node)
    export_class(TextureAtlas)
	export_class(TextureUnit)
	export_class(RenderTarget)
	export_class(RenderTexture)
    export_class(TextManager)
    export_class(Manager)
    export_class(Primitive)
    export_class(VertexData)
}
}

confirm_exports(ugdk_graphic)
