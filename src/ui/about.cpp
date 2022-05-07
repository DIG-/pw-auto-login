#include "ui/about.hpp"

#include <iup.h>
#include "version.hpp"

namespace DIG {
namespace UI {
namespace About {

constexpr auto _month(const char* date) {
  switch (date[0]) {
    case 'J':
      if (date[1] == 'a') {
        return "01";
      } else if (date[2] == 'n') {
        return "06";
      } else if (date[2] == 'l') {
        return "07";
      }

    case 'F':
      return "02";

    case 'M':
      switch (date[2]) {
        case 'r':
          return "03";
        case 'y':
          return "05";
      }

    case 'A':
      switch (date[1]) {
        case 'p':
          return "04";
        case 'u':
          return "08";
      }

    case 'S':
      return "09";

    case 'O':
      return "10";

    case 'N':
      return "11";

    case 'D':
      return "12";
  }
  return "00";
}

constexpr char _zis(const char value) {
  if (value == ' ')
    return '0';
  return value;
}

constexpr auto _build_date = __DATE__;
constexpr auto _build_month = _month(_build_date);
constexpr char build_date[] = {_zis(_build_date[7]),
                               _zis(_build_date[8]),
                               _zis(_build_date[9]),
                               _zis(_build_date[10]),
                               '-',
                               _zis(_build_date[4]),
                               _build_date[5],
                               '-',
                               _build_month[0],
                               _build_month[1]};

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
  IupSetAttribute(dialog, "ICON", "AAAAA");
  IupSetAttribute(dialog, "TITLE", "About");

  IupSetAttribute(about_version, "TITLE", VERSION::NAME);
  IupSetAttribute(about_date, "TITLE", build_date);

  IupPopup(dialog, IUP_CENTER, IUP_CENTER);
}

}  // namespace About
}  // namespace UI
}  // namespace DIG