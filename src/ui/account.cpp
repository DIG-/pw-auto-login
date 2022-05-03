#include "ui/account.hpp"

#include <iup.h>
#include <algorithm>
#include <sstream>
#include "crypto.hpp"
#include "current/server.hpp"
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

void apply(Data::Account& account) {
  account.username = IupGetAttribute(account_username, "VALUE");
  account.character = IupGetAttribute(account_character, "VALUE");
  account.command_line = IupGetAttribute(account_cmd, "VALUE");

  // Update password
  bool encrypt =
      account.password.compare(IupGetAttribute(account_password, "VALUE")) != 0;
  if (account.key.empty()) {
    encrypt = true;
    account.key = Crypto::random(32);
  }
  if (encrypt) {
    std::stringstream input(IupGetAttribute(account_password, "VALUE"));
    std::stringstream output;
    Crypto::encrypt(output, input, account.key);
    output.str(account.password);
  }

  // Update 64 bits
  std::string OPT_ON = "ON";
  if (OPT_ON.compare(IupGetAttribute(account_64_default, "VALUE")) == 0) {
    account.use64.reset();
  } else if (OPT_ON.compare(IupGetAttribute(account_64_yes, "VALUE")) == 0) {
    account.use64.emplace(true);
  } else {
    account.use64.emplace(false);
  }

  // Update Server
  std::string server = IupGetAttribute(account_server, "VALUE");
  if (server.empty()) {
    account.server.reset();
  } else if (!account.server.has_value() ||
             server.compare(account.server.value().name) != 0) {
    auto found = std::find_if(
        Server::list.begin(), Server::list.end(),
        [&server](auto& it) -> bool { return server.compare(it.name) == 0; });
    if (found != Server::list.end()) {
      account.server.emplace(*found);
    } else {
      account.server.reset();
    }
  }
}

void fill(Data::Account& account) {
  IupSetAttribute(account_username, "VALUE", account.username.c_str());
  IupSetAttribute(account_password, "VALUE", account.password.c_str());
  IupSetAttribute(account_character, "VALUE", account.character.c_str());
  IupSetAttribute(account_cmd, "VALUE", account.command_line.c_str());
  if (!account.use64.has_value()) {
    IupSetAttribute(account_64_default, "VALUE", "ON");
  } else if (account.use64.value()) {
    IupSetAttribute(account_64_yes, "VALUE", "ON");
  } else {
    IupSetAttribute(account_64_no, "VALUE", "ON");
  }
  if (account.server.has_value()) {
    IupSetAttribute(account_server, "VALUE",
                    account.server.value().name.c_str());
  }
}

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
    apply(*((Data::Account*)IupGetAttribute(dialog, ACCOUNT_POINTER)));
    *((bool*)IupGetAttribute(dialog, SAVE_BOOLEAN)) = true;
    IupDestroy(dialog);
    return 0;
  });

  {
    // TODO: Check if server selection is enabled
    if (Server::list.empty()) {
      Server::read();
    }
    uint_fast16_t count = 0;
    for (auto& server : Server::list) {
      IupSetAttribute(account_server, std::to_string(++count).c_str(),
                      server.name.c_str());
    }
    IupSetAttribute(account_server, std::to_string(++count).c_str(), nullptr);
  }

  fill(account);

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