#pragma once

#include <istream>
#include <ostream>
#include <string>

#include "error.hpp"

namespace DIG {
namespace Crypto {

Err encrypt(std::ostream&, std::istream&, const std::string&);
Err decrypt(std::ostream&, std::istream&, const std::string&);

}  // namespace Crypto
}  // namespace DIG