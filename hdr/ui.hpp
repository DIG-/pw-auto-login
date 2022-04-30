#pragma once

#include <string>

namespace DIG {
namespace UI {

bool is_initialized();
bool initialize();
bool destroy();

bool show_error_message(const std::string&, const bool = false);

}  // namespace UI
}  // namespace DIG