#include "ui.hpp"

#include <iup.h>

namespace DIG {
namespace UI {

std::string prompt(const std::string& title,
                   const std::string& message,
                   const bool password) {
  auto label = IupLabel(message.c_str());
  auto field = IupText(nullptr);
  auto filler = IupLabel("");
  auto ok = IupButton("&Ok", nullptr);
  auto cancel = IupButton("&Cancel", nullptr);
  // clang-format off
  auto dialog = IupDialog(
    IupVbox(
      label,
      field,
      IupHbox(filler, ok, cancel, nullptr),
      nullptr
    )
  );
  // clang-format on
  std::string output;
  IupSetAttribute(label, "EXPAND", "HORIZONTAL");
  IupSetAttribute(field, "EXPAND", "HORIZONTAL");
  IupSetAttribute(filler, "EXPAND", "HORIZONTAL");
  IupSetAttribute(dialog, "TITLE", title.c_str());
  IupSetAttribute(dialog, "RASTERSIZE", "120x0");
  IupSetAttribute(dialog, "RESIZE", "NO");
  IupPopup(dialog, IUP_CENTER, IUP_CENTER);
  return output;
}

std::string prompt_text(const std::string& title, const std::string& message) {
  return prompt(title, message, false);
}

std::string prompt_password(const std::string& title,
                            const std::string& message) {
  return prompt(title, message, true);
}

}  // namespace UI
}  // namespace DIG