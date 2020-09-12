#pragma once

#include <optional>

#include "data/server.hpp"

namespace DIG {
namespace Data {

typedef struct Login {
  std::string key;
  std::string username;
  std::string password;
  std::optional<Server> server;
} Login;

}  // namespace Data
}  // namespace DIG