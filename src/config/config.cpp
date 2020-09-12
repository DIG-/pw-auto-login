#include "config/config.hpp"

#include "os.hpp"

namespace DIG {
namespace Config {

extern Data::Config instance;

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
  return Err::NOT_IMPLEMENTED;
}

}  // namespace Config
}  // namespace DIG