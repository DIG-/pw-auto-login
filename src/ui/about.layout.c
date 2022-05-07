// This code was generated with xml-to-iup.
// Manual changes to this file will be overwritten if the code is regenerated.

Ihandle* create_layout() {
Ihandle* n_2 = IupLabel(nullptr);
Ihandle* n_4 = IupLabel("PW Auto Login");
Ihandle* n_6 = IupLabel("Version: ");
Ihandle* n_7 = IupLabel(nullptr);
Ihandle* n_5 = IupHbox(n_6, n_7, nullptr);
Ihandle* n_9 = IupLabel("Build Date: ");
Ihandle* n_10 = IupLabel(nullptr);
Ihandle* n_8 = IupHbox(n_9, n_10, nullptr);
Ihandle* n_12 = IupLabel("Compiler: ");
Ihandle* n_13 = IupLabel(nullptr);
Ihandle* n_11 = IupHbox(n_12, n_13, nullptr);
Ihandle* n_15 = IupLabel("License: ");
Ihandle* n_16 = IupLabel("CC BY-ND 4.0");
Ihandle* n_14 = IupHbox(n_15, n_16, nullptr);
Ihandle* n_3 = IupVbox(n_4, n_5, n_8, n_11, n_14, nullptr);
Ihandle* n_1 = IupHbox(n_2, n_3, nullptr);
Ihandle* n_17 = IupLabel(nullptr);
Ihandle* n_19 = IupLabel("Libraries");
Ihandle* n_21 = IupLabel("Mbed TLS: ");
Ihandle* n_22 = IupLabel(nullptr);
Ihandle* n_20 = IupHbox(n_21, n_22, nullptr);
Ihandle* n_24 = IupLabel("IUP: ");
Ihandle* n_25 = IupLabel(nullptr);
Ihandle* n_23 = IupHbox(n_24, n_25, nullptr);
Ihandle* n_27 = IupLabel("cxxopts: ");
Ihandle* n_28 = IupLabel(nullptr);
Ihandle* n_26 = IupHbox(n_27, n_28, nullptr);
Ihandle* n_30 = IupLabel("nlohmann::json: ");
Ihandle* n_31 = IupLabel(nullptr);
Ihandle* n_29 = IupHbox(n_30, n_31, nullptr);
Ihandle* n_18 = IupVbox(n_19, n_20, n_23, n_26, n_29, nullptr);
Ihandle* n_0 = IupVbox(n_1, n_17, n_18, nullptr);

// Attribute section
IupSetAttribute(n_2, "IMAGE", "DIG_LOGO");
IupSetAttribute(n_2, "RASTERSIZE", "64x64");
IupSetAttribute(n_4, "FONTSIZE", "22");
IupSetAttribute(n_3, "NMARGIN", "10x5");
IupSetAttribute(n_1, "ALIGNMENT", "ACENTER");
IupSetAttribute(n_17, "SEPARATOR", "horizontal");
IupSetAttribute(n_19, "FONTSIZE", "18");
IupSetAttribute(n_18, "NMARGIN", "10x5");

// Name section
IupSetHandle("about_version", n_7);
IupSetHandle("about_date", n_10);
IupSetHandle("about_compiler", n_13);
IupSetHandle("about_license", n_16);
IupSetHandle("about_lib_mbedtls", n_22);
IupSetHandle("about_lib_iup", n_25);
IupSetHandle("about_lib_cxxopts", n_28);
IupSetHandle("about_lib_json", n_31);
return n_0;
}