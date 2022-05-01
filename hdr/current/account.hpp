#pragma once

#include "data/account.hpp"
#include "error.hpp"

namespace DIG {
namespace Account {

extern Data::Account current;

Err create(const std::string&);

}  // namespace Account
}  // namespace DIG