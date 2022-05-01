#include <iup.h>

namespace DIG {
namespace UI {
namespace Main2 {

Ihandle* create_layout();

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
  IupShow(dialog);
}

// This code was generated with xml-to-iup.
// Manual changes to this file will be overwritten if the code is regenerated.

Ihandle* create_layout() {
Ihandle* n_2 = IupList(nullptr);
Ihandle* n_4 = IupButton("&Add", nullptr);
Ihandle* n_5 = IupLabel(nullptr);
Ihandle* n_6 = IupButton("&Edit", nullptr);
Ihandle* n_7 = IupLabel(nullptr);
Ihandle* n_8 = IupButton("&Remove", nullptr);
Ihandle* n_3 = IupHbox(n_4, n_5, n_6, n_7, n_8, nullptr);
Ihandle* n_9 = IupLabel(nullptr);
Ihandle* n_10 = IupButton("&Launch", nullptr);
Ihandle* n_1 = IupVbox(n_2, n_3, n_9, n_10, nullptr);
Ihandle* n_0 = IupFrame(n_1);

// Attribute section
IupSetAttribute(n_2, "RASTERSIZE", "200x150");
IupSetAttribute(n_4, "RASTERSIZE", "60x0");
IupSetAttribute(n_5, "EXPAND", "horizontal");
IupSetAttribute(n_6, "RASTERSIZE", "60x0");
IupSetAttribute(n_7, "EXPAND", "horizontal");
IupSetAttribute(n_8, "RASTERSIZE", "60x0");
IupSetAttribute(n_9, "RASTERSIZE", "10x10");
IupSetAttribute(n_10, "EXPAND", "horizontal");

// Name section
IupSetHandle("account_list", n_2);
IupSetHandle("account_add", n_4);
IupSetHandle("account_edit", n_6);
IupSetHandle("account_rem", n_8);
IupSetHandle("account_launch", n_10);
return n_0;
}

}  // namespace Main2
}  // namespace UI
}  // namespace DIG