#pragma once

#include <filesystem>
#include <string>
#include <vector>
#include "data/serialize.hpp"

namespace DIG {
namespace Data {

typedef struct KeyStore : Serializable {
  std::filesystem::path file;
  std::string key;
} KeyStore;

typedef struct Config : Serializable {
  std::filesystem::path path;
  std::filesystem::path game;
  std::vector<KeyStore> stores;
} Config;

}  // namespace Data
}  // namespace DIG