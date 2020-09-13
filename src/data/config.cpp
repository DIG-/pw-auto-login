#include "data/config.hpp"

#include "data/serialize.hpp"

namespace DIG {
namespace Data {

template <>
void to_json(nlohmann::json& json, const Config& config) {
  json = nlohmann::json{{"game", config.game}};
}

template <>
void from_json(const nlohmann::json& json, Config& config) {
  json.at("game").get_to(config.game);
}

}  // namespace Data
}  // namespace DIG

namespace nlohmann {

void adl_serializer<std::filesystem::path>::to_json(
    nlohmann::json& json,
    const std::filesystem::path& path) {
  json = path.string();
}

void adl_serializer<std::filesystem::path>::from_json(
    const nlohmann::json& json,
    std::filesystem::path& path) {
  auto temp = json.get<std::string>();
  path.assign(temp);
}

}  // namespace nlohmann