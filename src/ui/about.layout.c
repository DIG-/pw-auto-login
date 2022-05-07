// This code was generated with xml-to-iup.
// Manual changes to this file will be overwritten if the code is regenerated.

Ihandle* create_layout() {
Ihandle* n_2 = IupLabel(nullptr);
Ihandle* n_3 = IupLabel(nullptr);
Ihandle* n_5 = IupLabel("PW Auto Login");
Ihandle* n_7 = IupLabel("Version: ");
Ihandle* n_8 = IupLabel(nullptr);
Ihandle* n_6 = IupHbox(n_7, n_8, nullptr);
Ihandle* n_10 = IupLabel("Build Date: ");
Ihandle* n_11 = IupLabel(nullptr);
Ihandle* n_9 = IupHbox(n_10, n_11, nullptr);
Ihandle* n_13 = IupLabel("Compiler: ");
Ihandle* n_14 = IupLabel(nullptr);
Ihandle* n_12 = IupHbox(n_13, n_14, nullptr);
Ihandle* n_16 = IupLabel("License: ");
Ihandle* n_17 = IupLabel("CC BY-ND 4.0");
Ihandle* n_15 = IupHbox(n_16, n_17, nullptr);
Ihandle* n_4 = IupVbox(n_5, n_6, n_9, n_12, n_15, nullptr);
Ihandle* n_1 = IupHbox(n_2, n_3, n_4, nullptr);
Ihandle* n_18 = IupLabel(nullptr);
Ihandle* n_20 = IupLabel("Libraries");
Ihandle* n_22 = IupLabel("Mbed TLS: ");
Ihandle* n_23 = IupLabel(nullptr);
Ihandle* n_21 = IupHbox(n_22, n_23, nullptr);
Ihandle* n_25 = IupLabel("IUP: ");
Ihandle* n_26 = IupLabel(nullptr);
Ihandle* n_24 = IupHbox(n_25, n_26, nullptr);
Ihandle* n_28 = IupLabel("cxxopts: ");
Ihandle* n_29 = IupLabel(nullptr);
Ihandle* n_27 = IupHbox(n_28, n_29, nullptr);
Ihandle* n_31 = IupLabel("nlohmann::json: ");
Ihandle* n_32 = IupLabel(nullptr);
Ihandle* n_30 = IupHbox(n_31, n_32, nullptr);
Ihandle* n_33 = IupLabel(nullptr);
Ihandle* n_19 = IupVbox(n_20, n_21, n_24, n_27, n_30, n_33, nullptr);
Ihandle* n_0 = IupVbox(n_1, n_18, n_19, nullptr);

// Attribute section
IupSetAttribute(n_2, "IMAGE", "DIG_LOGO");
IupSetAttribute(n_2, "RASTERSIZE", "64x64");
IupSetAttribute(n_3, "RASTERSIZE", "10x10");
IupSetAttribute(n_5, "FONTSIZE", "22");
IupSetAttribute(n_1, "ALIGNMENT", "ACENTER");
IupSetAttribute(n_1, "NMARGIN", "10x5");
IupSetAttribute(n_18, "SEPARATOR", "horizontal");
IupSetAttribute(n_20, "FONTSIZE", "18");
IupSetAttribute(n_33, "RASTERSIZE", "5x5");
IupSetAttribute(n_19, "NMARGIN", "10x5");

// Name section
IupSetHandle("about_version", n_8);
IupSetHandle("about_date", n_11);
IupSetHandle("about_compiler", n_14);
IupSetHandle("about_license", n_17);
IupSetHandle("about_lib_mbedtls", n_23);
IupSetHandle("about_lib_iup", n_26);
IupSetHandle("about_lib_cxxopts", n_29);
IupSetHandle("about_lib_json", n_32);
return n_0;
}