#pragma once

#include <filesystem>
#include <nlohmann/json.hpp>
#include "data/config.hpp"
#include "is_type_in_namespace.hpp"

namespace DIG {
namespace Data {

template <typename T, std::enable_if_t<helper::is_type_in_namespace<T>("DIG::Data::"), int> = 0>
void to_json(nlohmann::json&, const T&);

template <typename T, std::enable_if_t<helper::is_type_in_namespace<T>("DIG::Data::"), int> = 0>
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