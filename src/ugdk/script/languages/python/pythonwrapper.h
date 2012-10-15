#ifndef UGDK_SCRIPT_PYTHON_PYTHONWRAPPER_H_
#define UGDK_SCRIPT_PYTHON_PYTHONWRAPPER_H_

#include <vector>
#include <ugdk/script/langwrapper.h>

namespace ugdk {
namespace script {

class VirtualObj;

namespace python {

typedef void (*PyInitFunction)(void);
typedef ugdk::script::Module<PyInitFunction> PythonModule;
typedef ugdk::script::InheritableLangWrapper<PyInitFunction> PythonWrapperBase;
typedef ugdk::script::python::PyInitFunction inittype;

#define PYTHON_INIT_FUNCTION_NAME(name) init_##name
#define PYTHON_INIT_FUNCTION_SIGNATURE(name) void PYTHON_INIT_FUNCTION_NAME(name)(void)
#define PYTHON_MODULE_NAME(name) "_" #name
#define PYTHON_NAMESPACE ::ugdk::script::python

class PythonWrapper : public PythonWrapperBase {
  public:
    PythonWrapper() : PythonWrapperBase("py", LANG(Python), "Python") {}
    virtual ~PythonWrapper() {}

    virtual VirtualData::Ptr NewData();

    virtual void ExecuteCode(const std::string& code);
    
    virtual VirtualObj LoadModule(const std::string& name);

    /// Initializes the LangWrapper (that is, the language's API. Returns bool telling if (true=) no problems occured.
    virtual bool Initialize();
    /// Finalizes the LangWrapper, finalizing any language specific stuff.
    virtual void Finalize();

    void PrintPythonExceptionDetails();

  private:
    //std::vector<Module> modules_;
};

}
}
}

#endif /* UGDK_SCRIPT_PYTHON_PYTHONWRAPPER_H_ */
