#include "data/account.hpp"
#include "data/serialize.hpp"

namespace DIG {
namespace Data {

template <>
void to_json(nlohmann::json& json, const Account& account) {
  json = nlohmann::json{{"k", account.key},
                        {"u", account.username},
                        {"p", account.password},
                        {"c", account.character}};
  if (account.server.has_value()) {
    json["s"] = account.server.value();
  }
}

template <>
void from_json(const nlohmann::json& json, Account& account) {
  json.at("k").get_to(account.key);
  json.at("u").get_to(account.username);
  json.at("p").get_to(account.password);
  json.at("c").get_to(account.character);
  if (json.contains("s")) {
    account.server.emplace(Server{});
    json.at("s").get_to(account.server.value());
  }
}

}  // namespace Data
}  // namespace DIG