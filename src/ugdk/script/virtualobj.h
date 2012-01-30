
#ifndef UGDK_SCRIPT_VIRTUALOBJ_H_
#define UGDK_SCRIPT_VIRTUALOBJ_H_

#include <memory>
#include <vector>
#include <string>

#include <ugdk/script/virtualdata.h>
#include <ugdk/script/type.h>

namespace ugdk {
namespace script {

class LangWrapper;

/// A proxy class wich represents virtual objects from scripting languages.
/**
 ** Designed for intuitive use.
 **
 ** TODO: explanations and examples.
 */
class VirtualObj {

  public:

    /// Builds an <i>empty</i> virtual object.
    /** Attempting to use any method in a virtual object created this way will
     ** result in a segmentation fault.
     */
    VirtualObj() :
        data_() {}

	explicit VirtualObj(VirtualData::Ptr data) :
	    data_(data) {}

	~VirtualObj();

	VirtualObj& operator =(const VirtualObj& rhs) {
	    data_ = rhs.data_->Copy();
	    return *this;
	}

	template <class T>
	T* value() const {
	    return static_cast <T*> (
	        data_->Unwrap(TypeRegistry<T>::type())
        );
	}

	template <class T>
	void set(T* obj) {
	    data_ = data_->Wrap(
            static_cast<void*>(obj),
            TypeRegistry<T>::type()
        );
	}

	LangWrapper* wrapper() const { return data_->wrapper(); }

	VirtualObj operator() (std::vector<VirtualObj> args) const {
		VirtualObj ret(data_->Execute(args));
		return ret;
	}

	VirtualObj operator[] (const std::string attr_name) const {
		VirtualObj attr(data_->GetAttribute(attr_name));
		return attr;
	}
	
	VirtualObj operator[] (const std::string attr_name) {
        VirtualObj attr(data_->GetAttribute(attr_name));
        return attr;
    }

	template <class T>
	static VirtualObj Create (T* obj, LangWrapper* wrapper) {
	    if (wrapper)
	        return VirtualObj(wrapper->WrapData(obj, TypeRegistry<T>::type()));
	    else return VirtualObj();
	}

  private:

	VirtualData::Ptr data_;

};

}
}

#endif /* UGDK_SCRIPT_VIRTUALOBJ_H_ */
