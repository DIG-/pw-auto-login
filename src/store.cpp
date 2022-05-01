#include "store.hpp"

#include <fstream>
#include <nlohmann/json.hpp>
#include <sstream>
#include "crypto.hpp"
#include "data/serialize.hpp"

namespace DIG {
namespace AccountStore {

Data::AccountStore open(const Data::AccountStoreInfo& info) {
  return open(info.file, info.key);
}

Data::AccountStore open(const std::filesystem::path& filename,
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

}  // namespace AccountStore
}  // namespace DIG