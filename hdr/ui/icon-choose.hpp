#pragma once

#include <filesystem>
#include <optional>

namespace DIG {
namespace UI {
namespace IconChoose {

bool choose(std::optional<std::filesystem::path>& icon);

}
}  // namespace UI
}  // namespace DIG