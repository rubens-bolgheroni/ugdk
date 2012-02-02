#include <ugdk/script/python/pythonvirtualdata.h>
#include <ugdk/script/scriptmanager.h>
#include <ugdk/script/virtualobj.h>
#include <ugdk/script/swig/swigpyrun.h>

#include <memory>
#include <cstdlib>

namespace ugdk {
namespace script {
namespace python {

using std::tr1::shared_ptr;

void* PythonVirtualData::Unwrap(const VirtualType& type) const {
	void* pointer;
	int res = SWIG_ConvertPtrAndOwn(py_data_, &pointer, type.FromLang(LANG(Python)), 0, NULL);
	if (SWIG_IsOK(res))
	    return pointer;
	return NULL;
}

/// Tries to wrap the given data with the given type into this object.
void PythonVirtualData::Wrap(void* data, const VirtualType& type) {
    if (py_data_ != NULL && own_ref_) {
        Py_DECREF(py_data_);
        py_data_ = NULL;
    }

    py_data_ = SWIG_NewInstanceObj(data, type.FromLang(LANG(Python)), 1);
    own_ref_ = true;
	/*Apparently, the PyObject return by the SWIG conversion function is a new reference.
	  So our PyVData needs to handle it.*/
}

void PythonVirtualData::Wrap(const char* str) {
    if (str == NULL)    return;
    if (py_data_ != NULL && own_ref_) {
        Py_DECREF(py_data_);
        py_data_ = NULL;
    }

    py_data_ = PyString_FromString(str);
    own_ref_ = true;
}

void PythonVirtualData::Wrap(bool boolean) {
    py_data_ = PyBool_FromLong(static_cast<long>(boolean));
    own_ref_ = true;
}

void PythonVirtualData::Wrap(int number) {
    if (py_data_ != NULL && own_ref_) {
        Py_DECREF(py_data_);
        py_data_ = NULL;
    }
    
    py_data_ = PyInt_FromLong(static_cast<long>(number));
    own_ref_ = true;
}

void PythonVirtualData::Wrap(double number) {
    if (py_data_ != NULL && own_ref_) {
        Py_DECREF(py_data_);
        py_data_ = NULL;
    }

    py_data_ = PyFloat_FromDouble(number);
    own_ref_ = true;
}

LangWrapper* PythonVirtualData::wrapper () const {
	return ScriptManager::ref()->GetWrapper("Python");
}

/// Tries to execute ourselves as a function in a script language,
/// passing the given arguments and returning the result.
VirtualData::Ptr PythonVirtualData::Execute(std::vector<Ptr> args) {
	if (!PyCallable_Check(py_data_)) {
		//The object we contain is not callable - cannot execute it.
		return VirtualData::Ptr();
	}

	PyObject* arglist = PyTuple_New(args.size()); //new ref
	if (arglist == NULL) {
		/*Some error occured... Py/C API doesn't specify what might cause the failure here...
		   Most likely out of memory? */
		return VirtualData::Ptr();
	}

	//PyTuple_SetItem(tuple, index(int), object) -> sets the element of the given index within the given tuple as the object passed
	// OBS.: steals the reference to object;  returns 0 on success
	for (unsigned int i = 0; i < args.size(); i++) {
		//check appropriate type of args[i]
		PythonVirtualData* py_arg = static_cast<PythonVirtualData*>(args[i].get());
		if (py_arg->own_ref_) {
			//this VData arg owns the ref to the Object it's pointing at. And since PyTuple_SetItem steals that reference...
			py_arg->own_ref_ = false;
		}
		else {
			//VData arg doesn't own its reference... We can't let PyTuple_SetItem steal a ref that isn't ours to begin with.
			Py_INCREF(py_arg->py_data_);
		}
		PyTuple_SetItem(arglist, i, py_arg->py_data_);
	}

	PyObject* result = PyObject_CallObject(py_data_, arglist); //return is new ref
	/*If result = NULL, CallObject failed (somehow), and due to the way we treat VirtualData in the system, 
	  this is the way to treat that.*/
	VirtualData::Ptr vdata( new PythonVirtualData(result, true) ); //PyVirtualData takes care of the ref.
	
	//Before returning, kill the argument tuple we created.
	Py_XDECREF(arglist);  //WARNING: in theory, this is correct. However in my testing (in the prototype) this cause some serious shit.
	
	return vdata;
}

/// Tries to get a attribute with the given name from this object.
VirtualData::Ptr PythonVirtualData::GetAttribute(const std::string attr_name) {
	PyObject* attr;
	
	/*We give preference for getting a object's attributes. If it doesn't have a attribute
	  with the given name, check if he has a item with key = attr_name */
	if (PyObject_HasAttrString(py_data_, attr_name.c_str())) {
		attr = PyObject_GetAttrString(py_data_, attr_name.c_str()); //return is new ref
	}
	else {
		if (!PyMapping_Check(py_data_)) {
			//Object doesn't have attribute with the given name and can't have items...
			return VirtualData::Ptr();
		}
		shared_ptr<char> str(new char(*(attr_name.c_str())), free);
		if (!PyMapping_HasKeyString(py_data_, str.get()) ) {
			//Object doesn't have attribute or item with the given name...
			return VirtualData::Ptr();
		}
		attr = PyMapping_GetItemString(py_data_, str.get()); //return is new ref
	}
	/*If Py_GetAttrString or Py_GetItemString failed somehow, they will return null.*/
	
	VirtualData::Ptr vdata( new PythonVirtualData(attr, true) );
	return vdata;
}

void PythonVirtualData::SetAttribute(Ptr attr_name, Ptr value) {
    PythonVirtualData* key = static_cast<PythonVirtualData*>(attr_name.get());
    PyObject* key_data = key->py_data_;
    PythonVirtualData* object = static_cast<PythonVirtualData*>(value.get());
    PyObject* object_data = object->py_data_;

    /*First we try checking if our object has a attribute or string with the given
      name to override it...*/
    if (PyObject_HasAttr(py_data_, key_data)) {
        PyObject_SetAttr(py_data_, key_data, object_data);
        return;
    }
    else if (PyMapping_Check(py_data_) && PyMapping_HasKey(py_data_, key_data)) {
        PyObject_SetItem(py_data_, key_data, object_data);
        return;
    }
}

}
}
}
