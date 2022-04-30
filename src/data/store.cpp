#include "data/store.hpp"
#include "data/serialize.hpp"

namespace DIG {
namespace Data {

template <>
void to_json(nlohmann::json& json, const AccountStore& store) {
  json = nlohmann::json{{"a", store.accounts}};
}

template <>
void from_json(const nlohmann::json& json, AccountStore& store) {
  json.at("a").get_to(store.accounts);
}

}  // namespace Data
}  // namespace DIG