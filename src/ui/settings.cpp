#include "ui/settings.hpp"

#include <iup.h>
#include <algorithm>
#include <cstring>
#include <iostream>
#include "current/config.hpp"
#include "ui.hpp"

namespace DIG {
namespace UI {
namespace Settings {

void open_settings() {
  auto& config = Config::instance;
  std::string game_ =
      ((config.game / "element") / "elementclient.exe").string();
  char game[1024];
  char cmd[2048];
  int use64 = config.use64 ? 0 : 1;
  int allow_server = config.allow_server ? 0 : 1;
  strcpy(game, game_.c_str());
  strcpy(cmd, config.command_line.c_str());

  if (!IupGetParam("Settings", nullptr, nullptr,
                   "Game: %f[OPEN|*.exe]\n64 bits: %o|Yes|No|\nAllow Server*: "
                   "%o|Yes|No|\nCommand Line: %m\n",
                   game, &use64, &allow_server, cmd)) {
    return;
  }

  // Game path
  std::filesystem::path parent = game;
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
  } else {
    config.game = parent;
  }

  // Format command line
  config.command_line = cmd;
  std::replace(config.command_line.begin(), config.command_line.end(), '\n',
               ' ');
  config.use64 = use64 == 0;
  config.allow_server = allow_server == 0;
  Config::save();
}

}  // namespace Settings
}  // namespace UI
}  // namespace DIG