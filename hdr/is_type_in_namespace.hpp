#pragma once
#include <type_traits>
#include <utility>

namespace helper {
class ctstring {
 public:
  constexpr ctstring(const char* string) : _string(string) {}

  constexpr const char* c_str() const { return _string; }

  constexpr bool begins_with(const ctstring other) const {
    return !*other.c_str() ||
           (*_string && *_string == *other.c_str() &&
            ctstring(_string + 1).begins_with(other.c_str() + 1));
  }

 private:
  const char* _string;
};

template <typename T>
constexpr bool is_type_in_namespace(const ctstring name) {
#if defined(_MSC_VER)
#define PRETTY_FUNCTION_OFFSET_1 \
  (sizeof("void __cdecl helper::is_type_in_namespace<struct ") - 1)
#define PRETTY_FUNCTION_OFFSET_2 \
  (sizeof("void __cdecl helper::is_type_in_namespace<class ") - 1)

  return ctstring(__FUNCSIG__ + PRETTY_FUNCTION_OFFSET_1).begins_with(name) ||
         ctstring(__FUNCSIG__ + PRETTY_FUNCTION_OFFSET_2).begins_with(name);

#undef PRETTY_FUNCTION_OFFSET_1
#undef PRETTY_FUNCTION_OFFSET_2
#elif defined(__clang__)
  return ctstring(__PRETTY_FUNCTION__ +
                  (sizeof("bool helper::is_type_in_namespace(const "
                          "helper::ctstring) [T = ") -
                   1))
      .begins_with(name);
#elif defined(__GNUC__)
  return ctstring(__PRETTY_FUNCTION__ +
                  (sizeof("constexpr bool "
                          "helper::is_type_in_namespace(helper::ctstring) "
                          "[with T = ") -
                   1))
      .begins_with(name);
#else
#error "Your compiler is not supported, yet."
#endif
}
}  // namespace helper