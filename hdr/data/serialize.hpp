#pragma once

#include <filesystem>
#include <nlohmann/json.hpp>
#include "data/config.hpp"

namespace DIG {
namespace Data {

typedef struct {
} Serializable;

template <typename T,
          std::enable_if_t<std::is_base_of_v<Serializable, T>, bool> = 0>
void to_json(nlohmann::json&, const T&);

template <typename T,
          std::enable_if_t<std::is_base_of_v<Serializable, T>, bool> = 0>
void from_json(const nlohmann::json&, T&);

}  // namespace Data
}  // namespace DIG

namespace nlohmann {
template <>
struct adl_serializer<std::filesystem::path> {
  static void to_json(nlohmann::json&, const std::filesystem::path&);
  static void from_json(const nlohmann::json&, std::filesystem::path&);
};
}  // namespace nlohmann