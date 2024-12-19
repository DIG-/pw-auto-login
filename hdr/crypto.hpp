#pragma once

#include <istream>
#include <ostream>
#include <string>
#include <cstdint>

#include "error.hpp"

namespace DIG {
namespace Crypto {

Err encrypt(std::ostream&, std::istream&, const std::string&) noexcept;
Err decrypt(std::ostream&, std::istream&, const std::string&) noexcept;
Err encode(std::ostream&, std::istream&) noexcept;
Err dencode(std::ostream&, std::istream&) noexcept;
std::string random(const uint_fast8_t&) noexcept;

}  // namespace Crypto
}  // namespace DIG