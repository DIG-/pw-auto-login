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
  read(instance, filename, key);
  UI::Main::update_account_store();
  return Err::OK;
}

Err open_first() {
  return open(Config::instance.stores[0]);
}

uint_fast16_t get_index() {
  auto& stores = Config::instance.stores;
  for (uint_fast16_t i = 0; i < stores.size(); i++) {
    if (stores[i].file == current_path) {
      return i;
    }
  }
  return -1;
}

Err save() {
  return save(instance, current_path, current_key);
}

}  // namespace AccountStore
}  // namespace DIG