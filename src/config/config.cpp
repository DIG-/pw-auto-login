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
  std::ofstream file(path, std::fstream::trunc);
  nlohmann::json json = instance;
  file << json.dump();
  file.close();
  return Err::OK;
}

}  // namespace Config
}  // namespace DIG