#pragma once

#include <filesystem>
#include <vector>

namespace DIG {
namespace Data {

typedef struct Config {
  std::filesystem::path game;
  std::vector<std::filesysten::path> stores;
} Config;

}  // namespace Data
}  // namespace DIG