#include "data/config.hpp"

#include "data/serialize.hpp"

namespace DIG {
namespace Data {

template <>
void to_json(nlohmann::json& json, const Config& config) {
  json = nlohmann::json{{"game", config.game},
                        {"stores", config.stores},
                        {"use64", config.use64},
                        {"allow_server", config.allow_server},
                        {"command_line", config.command_line}};
}

template <>
void from_json(const nlohmann::json& json, Config& config) {
  json.at("game").get_to(config.game);
  json.at("stores").get_to(config.stores);
  if (json.contains("use64")) {
    json.at("use64").get_to(config.use64);
  }
  if (json.contains("allow_server")) {
    json.at("allow_server").get_to(config.allow_server);
  }
  if (json.contains("command_line")) {
    json.at("command_line").get_to(config.command_line);
  }
}

template <>
void to_json(nlohmann::json& json, const AccountStoreInfo& ks) {
  json = nlohmann::json{{"file", ks.file}, {"key", ks.key}};
}

template <>
void from_json(const nlohmann::json& json, AccountStoreInfo& ks) {
  json.at("file").get_to(ks.file);
  json.at("key").get_to(ks.key);
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