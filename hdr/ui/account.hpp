#pragma once

#include <cstdint>
#include <optional>

namespace DIG {
namespace UI {
namespace Account {

enum class MoveDirection { UP, DOWN, TOP, BOTTOM };

bool add_account();
bool edit_account(const uint_fast16_t&);
bool rem_account(const uint_fast16_t&);
std::optional<uint_fast16_t> move_account(const uint_fast16_t&,
                                          const MoveDirection);

}  // namespace Account
}  // namespace UI
}  // namespace DIG