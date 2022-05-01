#pragma once

#include <istream>
#include <ostream>
#include <string>

#include "error.hpp"

namespace DIG {
namespace Crypto {

Err encrypt(std::ostream&, std::istream&, const std::string&);
Err decrypt(std::ostream&, std::istream&, const std::string&);
std::string random(const uint_fast8_t&);

}  // namespace Crypto
}  // namespace DIG