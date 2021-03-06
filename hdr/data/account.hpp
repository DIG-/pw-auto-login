#pragma once

#include <optional>

#include "data/serializable.hpp"
#include "data/server.hpp"

namespace DIG {
namespace Data {

typedef struct Account : Serializable {
  std::string key;
  std::string username;
  std::string password;
  std::string character;
  std::string command_line;
  std::optional<bool> use64;
  std::optional<Server> server;
} Account;

}  // namespace Data
}  // namespace DIG