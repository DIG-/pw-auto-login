#include "store.hpp"

#include <fstream>
#include <nlohmann/json.hpp>
#include <sstream>
#include "crypto.hpp"
#include "data/serialize.hpp"

namespace DIG {
namespace AccountStore {

Data::AccountStore read(const Data::AccountStoreInfo& info) {
  return read(info.file, info.key);
}

Data::AccountStore read(const std::filesystem::path& filename,
                        const std::string& key) {
  std::ifstream file(filename, std::ifstream::binary);
  std::stringstream buffer;
  Crypto::decrypt(buffer, file, key);
  nlohmann::json json;
  buffer >> json;
  Data::AccountStore store;
  json.get_to(store);
  return store;
}

Err save(const Data::AccountStore& store, const Data::AccountStoreInfo& info) {
  return save(store, info.file, info.key);
}

Err save(const Data::AccountStore& store,
         const std::filesystem::path& filename,
         const std::string& key) {
  nlohmann::json json = store;
  std::stringstream buffer;
  buffer << json;
  std::ofstream file(filename, std::ifstream::binary);
  Crypto::encrypt(file, buffer, key);
  return Err::OK;
}

}  // namespace AccountStore
}  // namespace DIG