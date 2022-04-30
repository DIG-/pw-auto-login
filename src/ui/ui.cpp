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

}  // namespace UI
}  // namespace DIG