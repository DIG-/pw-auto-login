#include "current/store.hpp"

#include "current/config.hpp"
#include "store.hpp"
#include "ui/main.hpp"

namespace DIG {
namespace AccountStore {

Data::AccountStore instance;
std::filesystem::path current_path;
std::string current_key;

Err open(const Data::AccountStoreInfo& info) {
  return open(info.file, info.key);
}

Err open(const std::filesystem::path& filename, const std::string& key) {
  current_path = filename;
  current_key = key;
  instance = read(filename, key);
  UI::Main::update_account_store();
  return Err::OK;
}

Err open_first() {
  return open(Config::instance.stores[0]);
}

Err save() {
  save(instance, current_path, current_key);
}

}  // namespace AccountStore
}  // namespace DIG