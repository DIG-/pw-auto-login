#include "current/store.hpp"

#include "store.hpp"

namespace DIG {
namespace AccountStore {

Data::AccountStore instance;

Err open(const Data::AccountStoreInfo& info) {
  return open(info.file, info.key);
}

Err open(const std::filesystem::path& filename, const std::string& key) {
  instance = read(filename, key);
  return Err::OK;
}

}  // namespace AccountStore
}  // namespace DIG