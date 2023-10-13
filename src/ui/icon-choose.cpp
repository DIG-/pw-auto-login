#include "ui/icon-choose.hpp"

#include <iup.h>

namespace DIG {
namespace UI {
namespace IconChoose {

#include "./icon-choose.layout.c"

bool choose(std::optional<std::filesystem::path>& icon) {
  auto dialog = IupDialog(create_layout());

  IupSetAttribute(dialog, "ICON", "AAAAA");
  IupSetAttribute(dialog, "RESIZE", "NO");
  IupSetAttribute(dialog, "MINBOX", "NO");
  IupSetAttribute(dialog, "TITLE", "Choose icon");
  IupPopup(dialog, IUP_CENTER, IUP_CENTER);
  return false;
}

}  // namespace IconChoose
}  // namespace UI
}  // namespace DIG