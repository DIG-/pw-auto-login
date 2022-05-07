#include "ui/about.hpp"

#include <iup.h>
#include "version.hpp"

namespace DIG {
namespace UI {
namespace About {

#include "about.layout.c"

void show_about() noexcept {
  auto dialog = IupDialog(create_layout());
  auto about_version = IupGetHandle("about_version");
  auto about_date = IupGetHandle("about_date");
  auto about_compiler = IupGetHandle("about_compiler");
  auto about_license = IupGetHandle("about_license");
  auto about_lib_mbedtls = IupGetHandle("about_lib_mbedtls");
  auto about_lib_iup = IupGetHandle("about_lib_iup");
  auto about_lib_cxxopts = IupGetHandle("about_lib_cxxopts");
  auto about_lib_json = IupGetHandle("about_lib_json");

  IupSetAttribute(dialog, "RESIZE", "NO");
  IupSetAttribute(dialog, "MINBOX", "NO");

  IupSetAttribute(about_version, "TITLE", VERSION::NAME);

  IupPopup(dialog, IUP_CENTER, IUP_CENTER);
}

}  // namespace About
}  // namespace UI
}  // namespace DIG