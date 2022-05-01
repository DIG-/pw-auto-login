#include "ui.hpp"

#include <iup.h>
#include "config/config.hpp"

namespace DIG {
namespace UI {

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
  return false;
}

void run_main() {
  Config::init();
  if (Config::instance.game.empty()) {
    if (!configure_game_executable()) {
      return;
    }
  }
  if (Config::instance.stores.empty()) {
    if (!create_default_storage()) {
      return;
    }
  }
}

}  // namespace UI
}  // namespace DIG