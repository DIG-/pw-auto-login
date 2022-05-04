#include "ui/settings.hpp"

#include <iup.h>
#include <cstring>
#include "current/config.hpp"

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
}

}  // namespace Settings
}  // namespace UI
}  // namespace DIG