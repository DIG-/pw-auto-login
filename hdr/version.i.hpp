#pragma once

#include <cstdint>

namespace DIG {
namespace VERSION {

constexpr uint_fast8_t MAJOR = ${VERSION_MAJOR};
constexpr uint_fast8_t MINOR = ${VERSION_MINOR};
constexpr uint_fast8_t PATCH = ${VERSION_PATCH};
constexpr auto NAME = "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}";

}  // namespace VERSION
}  // namespace DIG