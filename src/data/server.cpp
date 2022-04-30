#include "data/server.hpp"
#include "data/serialize.hpp"

namespace DIG {
namespace Data {

template <>
void to_json(nlohmann::json& json, const Server& server) {
  json = nlohmann::json{{"n", server.name}, {"a", server.address}};
}

template <>
void from_json(const nlohmann::json& json, Server& server) {
  json.at("n").get_to(server.name);
  json.at("a").get_to(server.address);
}

}  // namespace Data
}  // namespace DIG