#include "ui/account.hpp"

#include <iup.h>
#include "current/store.hpp"
#include "data/account.hpp"

namespace DIG {
namespace UI {
namespace Account {

#include "account.layout.c"

bool dialog(Data::Account& account, bool edit) {
  auto dialog = IupDialog(create_layout());
  IupPopup(dialog, IUP_CENTER, IUP_CENTER);
  return false;
}

bool add_account() {
  Data::Account account;
  auto edited = dialog(account, false);
  AccountStore::instance.accounts.push_back(account);
  // TODO: Save current AccountStore
  return edited;
}
bool edit_account(const uint_fast16_t& index) {
  auto edited = dialog(AccountStore::instance.accounts[index], true);
  // TODO: Save current AccountStore
  return edited;
}

}  // namespace Account
}  // namespace UI
}  // namespace DIG