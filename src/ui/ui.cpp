#include "ui.hpp"

#include <iup.h>

namespace DIG {
namespace UI {

bool initialized = false;

bool is_initialized() {
  return initialized;
}
bool initialize() {
  if (initialized) {
    return true;
  }
  int argc = 1;
  char** argv = new char*[1];
  argv[0] = (char*)"";
  IupOpen(&argc, &argv);
  delete argv;
  initialized = true;
  return true;
}
bool destroy() {
  if (!initialized) {
    return false;
  }
  IupClose();
  initialized = false;
  return true;
}

bool show_error_message(const std::string& message, const bool confirm) {
  bool single = !initialized;
  if (!initialized) {
    initialize();
  }

  auto dialog = IupMessageDlg();
  IupSetAttribute(dialog, "DIALOGTYPE", "ERROR");
  IupSetAttribute(dialog, "TITLE", "Error");
  if (confirm) {
    IupSetAttribute(dialog, "BUTTONS", "YESNO");
  }
  IupSetAttribute(dialog, "VALUE", message.c_str());
  IupPopup(dialog, IUP_CENTER, IUP_CENTER);

  bool answer =
      confirm
          ? std::string("1").compare(IupGetAttribute(dialog, "BUTTONRESPONSE"))
          : false;

  if (single) {
    destroy();
  }
  return answer;
}

void show_error_message(const Err& error) {
  show_error_message(std::string("An unexpected error occurred. Code #") +
                     std::to_string(error));
}

void show_game_launch_error(const Err& error) {
  switch (error) {
    case Err::FAILED_TO_SELECT_SERVER:
      show_error_message(
          "Failed to select server.\nFile accounts.txt can be protected.\n\nOr "
          "disable server feature.");
      break;

    case Err::REQUIRE_ADMIN:
      show_error_message(
          "Require admin permission to select server.\nRun this program (or "
          "shortcut) as admin.\n\nOr disable server feature.");
      break;

    default:
      show_error_message(std::string("Failed to launche game. Code #") +
                         std::to_string(error));
      break;
  }
}

}  // namespace UI
}  // namespace DIG