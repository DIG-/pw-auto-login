#pragma once

#include <string>
#include <vector>

#include "data/account.hpp"
#include "data/serializable.hpp"

namespace DIG {
namespace Data {

typedef struct AccountStore : Serializable {
  std::vector<Account> logins;
};

}  // namespace Data
}  // namespace DIG