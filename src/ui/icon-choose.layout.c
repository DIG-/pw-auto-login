// This code was generated with xml-to-iup.
// Manual changes to this file will be overwritten if the code is regenerated.

Ihandle* create_layout() {
Ihandle* n_5 = IupToggle("None", nullptr);
Ihandle* n_6 = IupToggle("Custom", nullptr);
Ihandle* n_4 = IupGridBox(n_5, n_6, nullptr);
Ihandle* n_3 = IupScrollBox(n_4);
Ihandle* n_2 = IupRadio(n_3);
Ihandle* n_1 = IupFrame(n_2);
Ihandle* n_8 = IupLabel(nullptr);
Ihandle* n_9 = IupButton("&Select", nullptr);
Ihandle* n_10 = IupLabel(nullptr);
Ihandle* n_11 = IupButton("&Cancel", nullptr);
Ihandle* n_7 = IupHbox(n_8, n_9, n_10, n_11, nullptr);
Ihandle* n_0 = IupVbox(n_1, n_7, nullptr);

// Attribute section
IupSetAttribute(n_4, "NUMDIV", "3");
IupSetAttribute(n_1, "RASTERSIZE", "300x400");
IupSetAttribute(n_8, "EXPAND", "horizontal");
IupSetAttribute(n_9, "RASTERSIZE", "60x0");
IupSetAttribute(n_10, "RASTERSIZE", "10x0");
IupSetAttribute(n_11, "RASTERSIZE", "60x0");

// Name section
IupSetHandle("icon_choose_none", n_5);
IupSetHandle("icon_choose_custom", n_6);
IupSetHandle("icon_choose_grid", n_4);
IupSetHandle("icon_choose_radio", n_2);
IupSetHandle("icon_choose_select", n_9);
IupSetHandle("icon_choose_cancel", n_11);
return n_0;
}