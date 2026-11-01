#pragma once

#include <string>

#include "data/serializable.hpp"

namespace DIG {
namespace Data {

typedef struct Server : Serializable {
  std::string name;
  std::string address;

  Server() = default;
  Server(const std::string& name, const std::string& address)
      : name(name), address(address) {}
} Server;

}  // namespace Data
}  // namespace DIG