#pragma once

#include <optional>

#include "data/server.hpp"

namespace DIG {
namespace Data {

typedef struct Account {
  std::string key;
  std::string username;
  std::string password;
  std::string character;
  std::optional<Server> server;
} Account;

}  // namespace Data
}  // namespace DIG