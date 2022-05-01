#include "ui/main.hpp"
#include "ui.hpp"

#include <iup.h>
#include "crypto.hpp"
#include "current/account.hpp"
#include "current/config.hpp"
#include "current/server.hpp"
#include "current/store.hpp"
#include "os.hpp"
#include "store.hpp"

namespace DIG {
namespace UI {
namespace Main {

Ihandle* account_list;
Ihandle* account_list_add;
Ihandle* account_list_del;
Ihandle* account_username;
Ihandle* account_password;
Ihandle* account_password_toggle;
Ihandle* account_character;
Ihandle* account_server;
Ihandle* account_save;
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
    parent = parent.parent_path();
    auto patcher = parent / "patcher";
    if (std::filesystem::exists(patcher) &&
        std::filesystem::is_directory(patcher)) {
      break;
    }
  }
  if (!parent.has_parent_path() &&
      std::filesystem::exists(parent / "patcher")) {
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

void create() {
  account_list = IupList(nullptr);
  account_list_add = IupButton("Add", nullptr);
  account_list_del = IupButton("Remove", nullptr);
  auto account_username_lbl = IupLabel("Username:");
  account_username = IupText(nullptr);
  auto account_password_lbl = IupLabel("Password:");
  account_password = IupText(nullptr);
  account_password_toggle = IupToggle("Edit", nullptr);
  auto account_character_lbl = IupLabel("Character:");
  account_character = IupText(nullptr);
  auto account_server_lbl = IupLabel("Server:");
  account_server = IupList(nullptr);
  auto account_save_lbl = IupLabel("");
  account_save = IupButton("Save", nullptr);
  auto account_launch_lbl = IupLabel("");
  account_launch = IupButton("Launch", nullptr);

  constexpr auto LABEL_SIZE = "60x0";
  constexpr auto FIELD_SIZE = "100x0";
  constexpr auto BUTTON_SIZE = "60x0";
  IupSetAttribute(account_list, "RASTERSIZE", "120x0");
  IupSetAttribute(account_list, "EXPAND", "VERTICAL");
  IupSetAttribute(account_list_add, "RASTERSIZE", BUTTON_SIZE);
  IupSetAttribute(account_list_del, "RASTERSIZE", BUTTON_SIZE);

  IupSetAttribute(account_username_lbl, "RASTERSIZE", LABEL_SIZE);
  IupSetAttribute(account_password_lbl, "RASTERSIZE", LABEL_SIZE);
  IupSetAttribute(account_character_lbl, "RASTERSIZE", LABEL_SIZE);
  IupSetAttribute(account_server_lbl, "RASTERSIZE", LABEL_SIZE);
  IupSetAttribute(account_save_lbl, "RASTERSIZE", LABEL_SIZE);
  IupSetAttribute(account_launch_lbl, "EXPAND", "HORIZONTAL");

  IupSetAttribute(account_username, "RASTERSIZE", FIELD_SIZE);
  IupSetAttribute(account_password, "RASTERSIZE", FIELD_SIZE);
  IupSetAttribute(account_character, "RASTERSIZE", FIELD_SIZE);
  IupSetAttribute(account_server, "RASTERSIZE", FIELD_SIZE);
  IupSetAttribute(account_save, "RASTERSIZE", BUTTON_SIZE);
  IupSetAttribute(account_launch, "RASTERSIZE", BUTTON_SIZE);

  IupSetAttribute(account_server, "DROPDOWN", "YES");
  IupSetCallback(account_list_add, "ACTION", [](Ihandle* ih) -> int {
    auto character = prompt_text("Add account", "Enter character name:");
    if (!character.empty()) {
      Account::create(character);
    }
    return 0;
  });

  // clang-format off
  auto grid = IupVbox(
    IupHbox(account_username_lbl, account_username, nullptr),
    IupHbox(account_password_lbl, account_password, account_password_toggle, nullptr),
    IupHbox(account_character_lbl, account_character, nullptr),
    IupHbox(account_server_lbl, account_server, nullptr),
    IupHbox(account_save_lbl, account_save, account_launch_lbl, account_launch, nullptr),
    nullptr
  );
  // clang-format on
  IupSetAttribute(grid, "NUMDIV", "2");
  // clang-format off
  auto layout = IupHbox(
    IupVbox(
      account_list,
      IupHbox(account_list_add, account_list_del, nullptr),
      nullptr
    ),
    IupFrame(grid),
    nullptr
  );
  // clang-format on
  auto window = IupDialog(layout);
  // IupSetAttribute(window, "RASTERSIZE", "512x0");
  IupSetAttribute(window, "TITLE", "PW Auto Login");
  IupSetAttribute(window, "RESIZE", "NO");
  IupShow(window);
  AccountStore::open_first();
  Server::read();
  {
    uint_fast16_t count = 0;
    for (auto server : Server::list) {
      count++;
      IupSetStrAttribute(account_server, std::to_string(count).c_str(),
                         server.name.c_str());
    }
    count++;
    IupSetStrAttribute(account_server, std::to_string(count).c_str(), nullptr);
  }
}

void disable_account_form() {
  IupSetAttribute(account_username, "ACTIVE", "NO");
  IupSetAttribute(account_username, "VALUE", "");
  IupSetAttribute(account_password, "ACTIVE", "NO");
  IupSetAttribute(account_password, "VALUE", "");
  IupSetAttribute(account_password_toggle, "ACTIVE", "NO");
  IupSetAttribute(account_character, "ACTIVE", "NO");
  IupSetAttribute(account_character, "VALUE", "");
  IupSetAttribute(account_server, "ACTIVE", "NO");
  IupSetAttribute(account_server, "VALUE", "");
  IupSetAttribute(account_save, "ACTIVE", "NO");
  IupSetAttribute(account_launch, "ACTIVE", "NO");
}
void enable_account_form() {
  IupSetAttribute(account_username, "ACTIVE", "YES");
  IupSetAttribute(account_password, "ACTIVE", "NO");
  IupSetAttribute(account_password_toggle, "ACTIVE", "YES");
  IupSetAttribute(account_character, "ACTIVE", "YES");
  IupSetAttribute(account_server, "ACTIVE", "YES");
  IupSetAttribute(account_save, "ACTIVE", "YES");
  IupSetAttribute(account_launch, "ACTIVE", "YES");
}

void select_account(const uint_fast8_t index) {
  enable_account_form();
  auto& account = AccountStore::instance.accounts[index];
  IupSetAttribute(account_username, "VALUE", account.username.c_str());
  IupSetAttribute(account_password, "VALUE", account.password.c_str());
  IupSetAttribute(account_character, "VALUE", account.character.c_str());
  if (account.server.has_value()) {
    IupSetAttribute(account_server, "VALUE",
                    account.server.value().name.c_str());
  } else {
    IupSetAttribute(account_server, "VALUE", "");
  }
}

void update_account_store() {
  uint_fast16_t count = 0;
  for (auto account : AccountStore::instance.accounts) {
    count++;
    IupSetAttribute(account_list, std::to_string(count).c_str(),
                    account.character.c_str());
  }
  count++;
  IupSetAttribute(account_list, std::to_string(count).c_str(), nullptr);
  if (count > 1) {
    IupSetAttribute(account_list, "VALUE", "1");
  } else {
    disable_account_form();
  }
}

void select_account(const uint_fast8_t& index) {
  IupSetAttribute(account_list, "VALUE", std::to_string(index + 1).c_str());
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
  Main::create();
  IupMainLoop();
}

}  // namespace UI
}  // namespace DIG