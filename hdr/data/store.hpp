#pragma once

#include <string>
#include <vector>

#include "data/account.hpp"
#include "data/serializable.hpp"

namespace DIG {
namespace Data {

typedef struct AccountStore : Serializable {
  std::vector<Account> accounts;
} AccountStore;

}  // namespace Data
}  // namespace DIG