#pragma once

#include <cstdint>
#include <optional>

namespace DIG {
namespace UI {
namespace Account {

bool add_account();
bool edit_account(const uint_fast16_t&);
bool rem_account(const uint_fast16_t&);
std::optional<uint_fast16_t> move_account(const uint_fast16_t&, bool up = false,
                                          bool down = false, bool top = false,
                                          bool bottom = false);

}  // namespace Account
}  // namespace UI
}  // namespace DIG