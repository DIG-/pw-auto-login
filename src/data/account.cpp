#include "data/account.hpp"
#include "data/serialize.hpp"

namespace DIG {
namespace Data {

template <>
void to_json(nlohmann::json& json, const Account& account) {
  json = nlohmann::json{{"k", account.key},
                        {"u", account.username},
                        {"p", account.password},
                        {"c", account.character},
                        {"cl", account.command_line}};
  if (account.use64.has_value()) {
    json["64"] = account.use64.value();
  }
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
  json.at("cl").get_to(account.command_line);
  if (json.contains("64")) {
    account.use64.emplace(false);
    json.at("64").get_to(account.use64.value());
  }
  if (json.contains("s")) {
    account.server.emplace(Server{});
    json.at("s").get_to(account.server.value());
  }
}

}  // namespace Data
}  // namespace DIG