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
  return Err::NOT_IMPLEMENTED;
}

Err save() {
  return save(default_config());
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