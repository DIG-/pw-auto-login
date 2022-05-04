#include "ui/main.hpp"
#include "ui.hpp"

#include <iup.h>
#include "crypto.hpp"
#include "current/account.hpp"
#include "current/config.hpp"
#include "current/server.hpp"
#include "current/store.hpp"
#include "game.hpp"
#include "os.hpp"
#include "store.hpp"
#include "ui/account.hpp"
#include "ui/settings.hpp"

namespace DIG {
namespace UI {
namespace Main {

#include "main.layout.c"

constexpr auto MENU = "DIG::UI::Main::Menu";
constexpr auto SETTINGS_ACTION = "DIG::UI::Main::Settings";

Ihandle* account_list;
Ihandle* account_add;
Ihandle* account_edit;
Ihandle* account_rem;
Ihandle* account_launch;

bool configure_game_executable() {
  show_error_message("Game executable not defined.");
  auto dialog = IupFileDlg();
  IupSetAttribute(dialog, "TITLE", "Select game client executable");
  IupSetAttribute(dialog, "EXTFILTER", "ElementClient|*.exe");
  IupSetAttribute(dialog, "FILE", "elementclient.exe");
  IupSetAttribute(dialog, "FILTER", "elementclient.exe;elementclient_64.exe");
  IupPopup(dialog, IUP_CENTER, IUP_CENTER);
  if (IupGetInt(dialog, "STATUS") != 0) {
    show_error_message("Require to select game executable to continue.");
    return false;
  }
  Config::instance.game = IupGetAttribute(dialog, "VALUE");
  std::filesystem::path parent = Config::instance.game;
  while (parent.has_parent_path()) {
    auto temp = parent.parent_path();
    if (temp == parent) {
      break;
    }
    parent = temp;
    auto patcher = parent / "patcher";
    if (std::filesystem::exists(patcher) &&
        std::filesystem::is_directory(patcher)) {
      break;
    }
  }
  if (!std::filesystem::exists(parent / "patcher")) {
    show_error_message("Failed to find game installation root.");
    return false;
  }
  if (Config::instance.game.string().find("64.exe") != std::string::npos) {
    Config::instance.use64 = true;
  }
  Config::instance.game = parent;
  Config::instance.command_line = "startbypatcher";
  Config::save();
  return true;
}

bool create_default_storage() {
  Data::AccountStore store;
  Data::AccountStoreInfo info;
  info.file = OS::data_dir() / "default.dat";
  info.key = Crypto::random(32);
  AccountStore::save(store, info);
  Config::instance.stores.push_back(info);
  Config::save();
  return false;
}

int_fast16_t get_selection() {
  auto attr = IupGetAttribute(account_list, "VALUE");
  std::string value;
  if (attr != nullptr) {
    value = attr;
  }
  int_fast16_t index = -1;
  if (!value.empty()) {
    index = std::stoi(value) - 1;
  }
  return index;
}

Data::Account& get_selected_account() {
  return AccountStore::instance.accounts[get_selection()];
}

void create_menu() {
  auto settings = IupItem("Settings", nullptr);
  // clang-format off
  auto menu = IupMenu(
    settings,
    nullptr
  );
  // clang-format on
  IupSetHandle(MENU, menu);
  IupSetCallback(settings, "ACTION", [](Ihandle* ih) -> int {
    Settings::open_settings();
    return 0;
  });
}

void create() {
  auto dialog = IupDialog(create_layout());
  create_menu();
  account_list = IupGetHandle("account_list");
  account_add = IupGetHandle("account_add");
  account_edit = IupGetHandle("account_edit");
  account_rem = IupGetHandle("account_rem");
  account_launch = IupGetHandle("account_launch");

  IupSetAttribute(dialog, "TITLE", "PW Auto Login");
  IupSetAttribute(dialog, "RESIZE", "NO");
  IupSetAttribute(dialog, "MENU", MENU);
  IupSetAttribute(dialog, "ICON", "MAIN_ICON");

  IupSetAttribute(account_edit, "ACTIVE", "NO");
  IupSetAttribute(account_rem, "ACTIVE", "NO");
  IupSetAttribute(account_launch, "ACTIVE", "NO");

  IupSetCallback(account_list, "VALUECHANGED_CB", [](Ihandle* ih) -> int {
    update_selection();
    return 0;
  });
  IupSetCallback(account_add, "ACTION", [](Ihandle* ih) -> int {
    if (Account::add_account()) {
      update_account_store();
      select_account(AccountStore::instance.accounts.size() - 1);
    }
    return 0;
  });
  IupSetCallback(account_edit, "ACTION", [](Ihandle* ih) -> int {
    if (Account::edit_account(get_selection())) {
      update_account_store();
    }
    return 0;
  });
  IupSetCallback(account_rem, "ACTION", [](Ihandle* ih) -> int {
    if (Account::rem_account(get_selection())) {
      update_account_store();
    }
    return 0;
  });
  IupSetCallback(account_launch, "ACTION", [](Ihandle* ih) -> int {
    auto e = Game::login(get_selected_account());
    if (e != Err::OK) {
      show_error_message(std::string("Failed to open game. #") +
                         std::to_string(e));
    }
    return 0;
  });

  update_account_store();

  IupShow(dialog);
}

void update_selection() {
  auto index = get_selection();
  if (index < 0) {
    IupSetAttribute(account_edit, "ACTIVE", "NO");
    IupSetAttribute(account_rem, "ACTIVE", "NO");
    IupSetAttribute(account_launch, "ACTIVE", "NO");
    return;
  }
  IupSetAttribute(account_edit, "ACTIVE", "YES");
  IupSetAttribute(account_rem, "ACTIVE", "YES");
  IupSetAttribute(account_launch, "ACTIVE", "YES");
}

void update_account_store() {
  auto& store = AccountStore::instance;
  uint_fast16_t count = 0;
  for (auto& account : store.accounts) {
    IupSetAttribute(account_list, std::to_string(++count).c_str(),
                    account.character.c_str());
  }
  IupSetAttribute(account_list, std::to_string(++count).c_str(), nullptr);
  update_selection();
}

void select_account(const uint_fast16_t& index) {
  IupSetAttribute(account_list, "VALUE", std::to_string(index + 1).c_str());
  update_selection();
}

}  // namespace Main

void run_main() {
  Config::init();
  if (Config::instance.game.empty()) {
    if (!Main::configure_game_executable()) {
      return;
    }
  }
  if (Config::instance.stores.empty()) {
    if (!Main::create_default_storage()) {
      return;
    }
  }
  AccountStore::open_first();
  Main::create();
  IupMainLoop();
}

}  // namespace UI
}  // namespace DIG