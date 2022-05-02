// This code was generated with xml-to-iup.
// Manual changes to this file will be overwritten if the code is regenerated.

Ihandle* create_layout() {
Ihandle* n_3 = IupLabel("Username:");
Ihandle* n_4 = IupText(nullptr);
Ihandle* n_2 = IupHbox(n_3, n_4, nullptr);
Ihandle* n_6 = IupLabel("Password:");
Ihandle* n_7 = IupText(nullptr);
Ihandle* n_5 = IupHbox(n_6, n_7, nullptr);
Ihandle* n_9 = IupLabel("Character:");
Ihandle* n_10 = IupText(nullptr);
Ihandle* n_8 = IupHbox(n_9, n_10, nullptr);
Ihandle* n_12 = IupLabel("Server:");
Ihandle* n_13 = IupList(nullptr);
Ihandle* n_11 = IupHbox(n_12, n_13, nullptr);
Ihandle* n_15 = IupLabel("64 bits:");
Ihandle* n_16 = IupToggle(nullptr, nullptr);
Ihandle* n_14 = IupHbox(n_15, n_16, nullptr);
Ihandle* n_17 = IupLabel("Extra command line:");
Ihandle* n_18 = IupText(nullptr);
Ihandle* n_19 = IupLabel(nullptr);
Ihandle* n_21 = IupLabel(nullptr);
Ihandle* n_22 = IupButton("&Save", nullptr);
Ihandle* n_23 = IupLabel(nullptr);
Ihandle* n_24 = IupButton("&Cancel", nullptr);
Ihandle* n_20 = IupHbox(n_21, n_22, n_23, n_24, nullptr);
Ihandle* n_1 = IupVbox(n_2, n_5, n_8, n_11, n_14, n_17, n_18, n_19, n_20, nullptr);
Ihandle* n_0 = IupFrame(n_1);

// Attribute section
IupSetAttribute(n_3, "RASTERSIZE", "100x0");
IupSetAttribute(n_6, "RASTERSIZE", "100x0");
IupSetAttribute(n_7, "PASSWORD", "yes");
IupSetAttribute(n_9, "RASTERSIZE", "100x0");
IupSetAttribute(n_12, "RASTERSIZE", "100x0");
IupSetAttribute(n_13, "DROPDOWN", "yes");
IupSetAttribute(n_15, "RASTERSIZE", "100x0");
IupSetAttribute(n_16, "3STATE", "YES");
IupSetAttribute(n_16, "VALUE", "NOTDEF");
IupSetAttribute(n_18, "EXPAND", "horizontal");
IupSetAttribute(n_19, "SEPARATOR", "horizontal");
IupSetAttribute(n_19, "RASTERSIZE", "0x10");
IupSetAttribute(n_21, "EXPAND", "horizontal");
IupSetAttribute(n_23, "RASTERSIZE", "10x0");

// Name section
IupSetHandle("account_username", n_4);
IupSetHandle("account_password", n_7);
IupSetHandle("account_character", n_10);
IupSetHandle("account_server", n_13);
IupSetHandle("account_64", n_16);
IupSetHandle("account_cmd", n_18);
return n_0;
}