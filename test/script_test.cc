#include <ugdk/system/config.h>

#ifdef UGDK_PYTHON_ENABLED
#include <Python.h>
#endif

#include <cstdlib>

#include <ugdk/system/engine.h>
#include <ugdk/script.h>
#include <ugdk/script/scriptmanager.h>
#include <ugdk/script/virtualobj.h>

using ugdk::script::VirtualObj;

static bool LuaTests() {
    VirtualObj main = SCRIPT_MANAGER()->LoadModule("main");
    if(!main) return false;
    VirtualObj val = main["integer"];

    auto f = main["soma"].AsFunction<int (int, int)>();
    assert(f(13, 25) == 38);
    assert(main["soma"].Call(3, val).value<int>() == 45);
    return main["soma"].Call(3, 8).value<int>() == 11;
}

static bool PythonTests() {
    VirtualObj wassup = SCRIPT_MANAGER()->LoadModule("wassup");
    if(!wassup) return false;
    if(!wassup["supimpa"]) return false;

    return wassup["supimpa"](wassup["vecx"]).valid();
}

int main(int argc, char **argv) {
    ugdk::system::Configuration config;
    config.base_path = "data/";
    config.audio_enabled = false;
    config.input_enabled = false;
    config.windows_list.clear();
    
    ugdk::script::InitScripts();
    
    ugdk::system::Initialize(config);

#ifdef UGDK_LUA_ENABLED
    if(!LuaTests()) puts("LUA FAILED!");
#endif

#ifdef UGDK_PYTHON_ENABLED
    PyObject *path = PySys_GetObject("path");
    PyList_Append(path, PyString_FromString("../src/generated"));
    if(!PythonTests()) puts("PYTHON FAILED!");
#endif
    
    ugdk::system::Run();
    ugdk::system::Release();
    return 0;
}
