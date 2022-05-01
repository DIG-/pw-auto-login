#include "current/store.hpp"

#include "current/config.hpp"
#include "store.hpp"
#include "ui/main.hpp"

namespace DIG {
namespace AccountStore {

Data::AccountStore instance;

Err open(const Data::AccountStoreInfo& info) {
  return open(info.file, info.key);
}

Err open(const std::filesystem::path& filename, const std::string& key) {
  instance = read(filename, key);
  UI::Main::update_account_store();
  return Err::OK;
}

Err open_first() {
  return open(Config::instance.stores[0]);
}

}  // namespace AccountStore
}  // namespace DIG