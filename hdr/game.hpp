#pragma once

#include "data/account.hpp"
#include "error.hpp"

namespace DIG {
namespace Game {

Err login(const Data::Account&);

}
}  // namespace DIG