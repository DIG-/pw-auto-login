#include <iup.h>

namespace DIG {
namespace UI {
namespace Main2 {

#include "main.c"

Ihandle* account_list;
Ihandle* account_add;
Ihandle* account_edit;
Ihandle* account_rem;
Ihandle* account_launch;

void create() {
  auto dialog = IupDialog(create_layout());
  account_list = IupGetHandle("account_list");
  account_add = IupGetHandle("account_add");
  account_edit = IupGetHandle("account_edit");
  account_rem = IupGetHandle("account_rem");
  account_launch = IupGetHandle("account_launch");

  IupSetAttribute(dialog, "TITLE", "PW Auto Login");
  IupSetAttribute(dialog, "RESIZE", "NO");

  IupSetAttribute(account_edit, "ACTIVE", "NO");
  IupSetAttribute(account_rem, "ACTIVE", "NO");
  IupSetAttribute(account_launch, "ACTIVE", "NO");

  IupShow(dialog);
}

}  // namespace Main2
}  // namespace UI
}  // namespace DIG