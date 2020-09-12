#pragma once

#include <filesystem>

#include "error.hpp"

namespace DIG {
namespace Config {

Err init();
Err init(const std::filesystem::path&);

}  // namespace Config
}  // namespace DIG