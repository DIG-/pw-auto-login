#pragma once

#include <filesystem>

#include "data/config.hpp"
#include "error.hpp"

namespace DIG {
namespace Config {

extern Data::Config instance;

Err init();
Err init(const std::filesystem::path&);
Err save();
Err save(const std::filesystem::path&);

}  // namespace Config
}  // namespace DIG