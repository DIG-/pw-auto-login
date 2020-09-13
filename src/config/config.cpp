#include "config/config.hpp"

#include <fstream>
#include "data/serialize.hpp"
#include "os.hpp"

namespace DIG {
namespace Config {

Data::Config instance;

const inline std::filesystem::path default_config() {
  return OS::data_dir() / "config.json";
}

Err init() {
  return init(default_config());
}

Err init(const std::filesystem::path& path) {
  instance.path = path;
  if (!std::filesystem::exists(path)) {
    return Err::FILE_DOES_NOT_EXISTS;
  }
  std::ifstream file(path);
  if (!file.is_open()) {
    return Err::CAN_NOT_OPEN_FILE;
  }

  nlohmann::json json;
  file >> json;
  file.close();
  json.get_to(instance);
  instance.path = path;

  return Err::OK;
}

Err save() {
  auto path = instance.path.empty() ? default_config() : instance.path;
  return save(path);
}

Err save(const std::filesystem::path& path) {
  auto parent = path.parent_path();
  if (!std::filesystem::exists(parent)) {
    if (!std::filesystem::create_directories(parent)) {
      return Err::CAN_NOT_CREATE_FOLDER;
    }
  }

  std::ofstream file(path, std::fstream::trunc);
  if (!file.is_open()) {
    return Err::CAN_NOT_OPEN_FILE;
  }

  nlohmann::json json = instance;
  file << json.dump();
  file.close();
  return Err::OK;
}

}  // namespace Config
}  // namespace DIG