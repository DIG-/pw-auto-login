// This code was generated with xml-to-iup.
// Manual changes to this file will be overwritten if the code is regenerated.

Ihandle* create_layout() {
Ihandle* n_3 = IupButton("/\\\n/\\", nullptr);
Ihandle* n_4 = IupButton("/\\", nullptr);
Ihandle* n_5 = IupButton("\\/", nullptr);
Ihandle* n_6 = IupButton("\\/\n\\/", nullptr);
Ihandle* n_2 = IupVbox(n_3, n_4, n_5, n_6, nullptr);
Ihandle* n_7 = IupList(nullptr);
Ihandle* n_9 = IupButton("&Add", nullptr);
Ihandle* n_10 = IupButton("&Edit", nullptr);
Ihandle* n_11 = IupButton("&Remove", nullptr);
Ihandle* n_12 = IupLabel(nullptr);
Ihandle* n_13 = IupLabel(nullptr);
Ihandle* n_14 = IupLabel(nullptr);
Ihandle* n_15 = IupButton("&Create Link", nullptr);
Ihandle* n_16 = IupLabel(nullptr);
Ihandle* n_17 = IupButton("&Launch", nullptr);
Ihandle* n_8 = IupVbox(n_9, n_10, n_11, n_12, n_13, n_14, n_15, n_16, n_17, nullptr);
Ihandle* n_1 = IupHbox(n_2, n_7, n_8, nullptr);
Ihandle* n_0 = IupFrame(n_1);

// Attribute section
IupSetAttribute(n_3, "EXPAND", "vertical");
IupSetAttribute(n_4, "EXPAND", "vertical");
IupSetAttribute(n_5, "EXPAND", "vertical");
IupSetAttribute(n_6, "EXPAND", "vertical");
IupSetAttribute(n_7, "RASTERSIZE", "200x150");
IupSetAttribute(n_9, "RASTERSIZE", "100x0");
IupSetAttribute(n_10, "RASTERSIZE", "100x0");
IupSetAttribute(n_11, "RASTERSIZE", "100x0");
IupSetAttribute(n_12, "EXPAND", "vertical");
IupSetAttribute(n_13, "SEPARATOR", "horizontal");
IupSetAttribute(n_14, "RASTERSIZE", "2x2");
IupSetAttribute(n_15, "RASTERSIZE", "100x0");
IupSetAttribute(n_16, "RASTERSIZE", "5x5");
IupSetAttribute(n_17, "EXPAND", "horizontal");

// Name section
IupSetHandle("account_move_top", n_3);
IupSetHandle("account_move_above", n_4);
IupSetHandle("account_move_bellow", n_5);
IupSetHandle("account_move_bottom", n_6);
IupSetHandle("account_list", n_7);
IupSetHandle("account_add", n_9);
IupSetHandle("account_edit", n_10);
IupSetHandle("account_rem", n_11);
IupSetHandle("account_link", n_15);
IupSetHandle("account_launch", n_17);
return n_0;
}