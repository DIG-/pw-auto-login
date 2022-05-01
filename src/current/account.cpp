#include "current/account.hpp"

#include "current/store.hpp"
#include "ui/main.hpp"

namespace DIG {
namespace Account {

Data::Account current;

Err create(const std::string& character) {
  AccountStore::instance.accounts.push_back({character : character});
  UI::Main::update_account_store();
  UI::Main::select_account(AccountStore::instance.accounts.size() - 1);
  return Err::OK;
}

}  // namespace Account
}  // namespace DIG