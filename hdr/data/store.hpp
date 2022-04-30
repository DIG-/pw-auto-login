#pragma once

#include <string>
#include <vector>

#include "data/account.hpp"

namespace DIG {
namespace Data {

typedef struct AccountStore {
  std::vector<Account> logins;
};

}  // namespace Data
}  // namespace DIG