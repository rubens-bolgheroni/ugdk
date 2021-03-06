#ifndef UGDK_SYSTEM_COMPATIBILITY_H_
#define UGDK_SYSTEM_COMPATIBILITY_H_

#include <memory>
#include <type_traits>

namespace ugdk {

    template <typename T, typename... Args> inline
    typename std::enable_if<!std::is_array<T>::value, std::unique_ptr<T>>::type
    MakeUnique(Args&&... args) {
        return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
    }

    template <typename T> inline
    typename std::enable_if<std::is_array<T>::value && std::extent<T>::value == 0, std::unique_ptr<T>>::type
    MakeUnique(std::size_t size) {
        using Element = typename std::remove_extent<T>::type;
        return std::unique_ptr<T>(new Element[size]);
    }

    template <typename T, typename... Args> inline
    typename std::enable_if<std::extent<T>::value != 0, void>::type
    MakeUnique(std::size_t size) = delete;
}

#endif // UGDK_SYSTEM_COMPATIBILITY_H_
