%module ugdk_input

%include <module/export.swig>

%{

#include <ugdk/input/keys.h>
#include <ugdk/input/keyboard.h>
#include <ugdk/input/mouse.h>
#include <ugdk/input/manager.h>
#include <ugdk/input/module.h>

%}

%import(module="ugdk_math") <ugdk/math/vector2D.h>
%import(module="ugdk_system") <ugdk/structure/types.h>
%import(module="ugdk_internal") <ugdk/internal.h>

%newobject ugdk::input::Manager::GetMousePosition();

%include <ugdk/input/keys.h>
%include <ugdk/input/keyboard.h>
%include <ugdk/input/mouse.h>
%include <ugdk/input/manager.h>
%include <ugdk/input/module.h>

namespace ugdk {
namespace input {
    export_class(Key)
    export_class(MouseButton)
    export_class(Manager)
	 export_class(Keyboard)
	 export_class(Mouse)
}
}
 
confirm_exports(ugdk_input)
