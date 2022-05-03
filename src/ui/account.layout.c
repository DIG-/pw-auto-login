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
Ihandle* n_18 = IupToggle("Default", nullptr);
Ihandle* n_19 = IupToggle("Yes", nullptr);
Ihandle* n_20 = IupToggle("No", nullptr);
Ihandle* n_17 = IupHbox(n_18, n_19, n_20, nullptr);
Ihandle* n_16 = IupRadio(n_17);
Ihandle* n_14 = IupHbox(n_15, n_16, nullptr);
Ihandle* n_21 = IupLabel("Extra command line:");
Ihandle* n_22 = IupText(nullptr);
Ihandle* n_23 = IupLabel(nullptr);
Ihandle* n_25 = IupLabel(nullptr);
Ihandle* n_26 = IupButton("&Save", nullptr);
Ihandle* n_27 = IupLabel(nullptr);
Ihandle* n_28 = IupButton("&Cancel", nullptr);
Ihandle* n_24 = IupHbox(n_25, n_26, n_27, n_28, nullptr);
Ihandle* n_1 = IupVbox(n_2, n_5, n_8, n_11, n_14, n_21, n_22, n_23, n_24, nullptr);
Ihandle* n_0 = IupFrame(n_1);

// Attribute section
IupSetAttribute(n_3, "RASTERSIZE", "80x0");
IupSetAttribute(n_4, "EXPAND", "horizontal");
IupSetAttribute(n_6, "RASTERSIZE", "80x0");
IupSetAttribute(n_7, "PASSWORD", "yes");
IupSetAttribute(n_7, "EXPAND", "horizontal");
IupSetAttribute(n_9, "RASTERSIZE", "80x0");
IupSetAttribute(n_10, "EXPAND", "horizontal");
IupSetAttribute(n_12, "RASTERSIZE", "80x0");
IupSetAttribute(n_13, "DROPDOWN", "yes");
IupSetAttribute(n_13, "EXPAND", "horizontal");
IupSetAttribute(n_15, "RASTERSIZE", "80x0");
IupSetAttribute(n_22, "EXPAND", "horizontal");
IupSetAttribute(n_23, "RASTERSIZE", "0x10");
IupSetAttribute(n_25, "EXPAND", "horizontal");
IupSetAttribute(n_26, "RASTERSIZE", "60x0");
IupSetAttribute(n_27, "RASTERSIZE", "10x0");
IupSetAttribute(n_28, "RASTERSIZE", "60x0");

// Name section
IupSetHandle("account_username", n_4);
IupSetHandle("account_password", n_7);
IupSetHandle("account_character", n_10);
IupSetHandle("account_server", n_13);
IupSetHandle("account_64_default", n_18);
IupSetHandle("account_64_yes", n_19);
IupSetHandle("account_64_no", n_20);
IupSetHandle("account_cmd", n_22);
IupSetHandle("account_save", n_26);
IupSetHandle("account_cancel", n_28);
return n_0;
}