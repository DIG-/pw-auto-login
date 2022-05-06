#pragma once

#include <string>
#include "error.hpp"

namespace DIG {
namespace UI {

bool is_initialized();
bool initialize();
void run_main();
bool destroy();

bool show_error_message(const std::string&, const bool = false);
void show_error_message(const Err&);
void show_game_launch_error(const Err&);
std::string prompt_text(const std::string&, const std::string&);
std::string prompt_password(const std::string&, const std::string&);

}  // namespace UI
}  // namespace DIG