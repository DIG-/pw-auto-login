#pragma once

#include <string>
#include "data/serializable.hpp"

namespace DIG {
namespace Data {

typedef struct Server : Serializable {
  std::string name;
  std::string address;
} Server;

}  // namespace Data
}  // namespace DIG