%module ugdk_system

%include <module/util_ugdk.swig>

%include "std_string.i"
%include "std_map.i"
%include "std_vector.i"

%{

#include <ugdk/action/scene.h>
#include <ugdk/structure/types.h>
#include <ugdk/system/configuration.h>
#include <ugdk/system/engine.h>
#include <ugdk/system/task.h>
#include <ugdk/system/taskplayer.h>

%}

%import(module="ugdk_action") <ugdk/action.h>
%import(module="ugdk_debug") <ugdk/debug.h>
%import(module="ugdk_math") <ugdk/math.h>
%import(module="ugdk_math") <ugdk/math/vector2D.h>

// For Configuration
%import(module="ugdk_desktop") <ugdk/desktop.h>


%include <ugdk/system.h>
%include <ugdk/structure/types.h>
%include <ugdk/system/configuration.h>
%include <ugdk/system/engine.h>
%include <ugdk/system/taskplayer.h>

namespace ugdk {
namespace system {
	export_class(Configuration)
	export_class(TaskPlayer)
} 
}
 
confirm_exports(ugdk_system)
