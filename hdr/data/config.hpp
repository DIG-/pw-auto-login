#pragma once

#include <filesystem>
#include <string>
#include <vector>
#include "data/serialize.hpp"

namespace DIG {
namespace Data {

typedef struct AccountStoreInfo : Serializable {
  std::filesystem::path file;
  std::string key;
} AccountStoreInfo;

typedef struct Config : Serializable {
  std::filesystem::path path;
  std::filesystem::path game;
  std::vector<AccountStoreInfo> stores;
} Config;

}  // namespace Data
}  // namespace DIG