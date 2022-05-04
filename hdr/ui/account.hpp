#pragma once

#include <cstdint>

namespace DIG {
namespace UI {
namespace Account {

bool add_account();
bool edit_account(const uint_fast16_t&);
bool rem_account(const uint_fast16_t&);

}  // namespace Account
}  // namespace UI
}  // namespace DIG