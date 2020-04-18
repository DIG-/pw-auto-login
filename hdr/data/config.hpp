#pragma once

#include <filesystem>
#include <vector>
#include <string>

namespace DIG {
namespace Data {

typedef struct KeyStore {
  std::filesystem::path filename;
  std::string key;
};

typedef struct Config {
  std::filesystem::path game;
  std::vector<KeyStore> stores;
} Config;

}  // namespace Data
}  // namespace DIG