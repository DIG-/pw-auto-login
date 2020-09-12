#pragma once

#include <string>
#include <vector>

#include "data/login.hpp"

namespace DIG {
namespace Data {

typedef struct Store {
  std::vector<Login> logins;
};

}  // namespace Data
}  // namespace DIG