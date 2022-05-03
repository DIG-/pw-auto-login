#include "ui/account.hpp"

#include <iup.h>
#include "current/store.hpp"
#include "data/account.hpp"

namespace DIG {
namespace UI {
namespace Account {

#include "account.layout.c"

Ihandle* dialog = nullptr;
Ihandle* account_username = nullptr;
Ihandle* account_password = nullptr;
Ihandle* account_character = nullptr;
Ihandle* account_server = nullptr;
Ihandle* account_64_default = nullptr;
Ihandle* account_64_yes = nullptr;
Ihandle* account_64_no = nullptr;
Ihandle* account_cmd = nullptr;

constexpr auto ACCOUNT_POINTER = "DIG::UI::Account::Dialog::Pointer";
constexpr auto SAVE_BOOLEAN = "DIG::UI::Account::Dialog::Save";

bool show_dialog(Data::Account& account, bool edit) {
  dialog = IupDialog(create_layout());
  bool save = false;
  account_username = IupGetHandle("account_username");
  account_password = IupGetHandle("account_password");
  account_character = IupGetHandle("account_character");
  account_server = IupGetHandle("account_server");
  account_64_default = IupGetHandle("account_64_default");
  account_64_yes = IupGetHandle("account_64_yes");
  account_64_no = IupGetHandle("account_64_no");
  account_cmd = IupGetHandle("account_cmd");
  auto account_save = IupGetHandle("account_save");
  auto account_cancel = IupGetHandle("account_cancel");

  IupSetAttribute(dialog, SAVE_BOOLEAN, (char*)&save);
  IupSetAttribute(dialog, ACCOUNT_POINTER, (char*)&account);

  IupSetCallback(account_cancel, "ACTION", [](Ihandle* ih) -> int {
    IupDestroy(dialog);
    return 0;
  });
  IupSetCallback(account_save, "ACTION", [](Ihandle* ih) -> int {
    IupDestroy(dialog);
    return 0;
  });

  IupPopup(dialog, IUP_CENTER, IUP_CENTER);
  return save;
}

bool add_account() {
  Data::Account account;
  auto edited = show_dialog(account, false);
  AccountStore::instance.accounts.push_back(account);
  // TODO: Save current AccountStore
  return edited;
}
bool edit_account(const uint_fast16_t& index) {
  auto edited = show_dialog(AccountStore::instance.accounts[index], true);
  // TODO: Save current AccountStore
  return edited;
}

}  // namespace Account
}  // namespace UI
}  // namespace DIG