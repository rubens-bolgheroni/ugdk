#ifndef UGDK_INPUT_MODULE_H_
#define UGDK_INPUT_MODULE_H_

#include <ugdk/input/manager.h>

namespace ugdk {
namespace input {

/// Initializes the module with the given Manager.
bool Initialize(Manager* manager);

/// Releases the module, disabling it.
void Release();

/// Getter for the manager of the module.
Manager* manager();

} // namespace input
} // namespace ugdk

#endif // UGDK_INPUT_MODULE_H_
