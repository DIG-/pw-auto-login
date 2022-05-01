#include "current/account.hpp"

#include "current/store.hpp"

namespace DIG {
namespace Account {

Data::Account current;

Err create(const std::string& character) {
  return Err::NOT_IMPLEMENTED;
}

}  // namespace Account
}  // namespace DIG