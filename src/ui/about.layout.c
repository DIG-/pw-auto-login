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
Ihandle* n_18 = IupLabel("Libraries");
Ihandle* n_20 = IupLabel("Mbed TLS: ");
Ihandle* n_21 = IupLabel(nullptr);
Ihandle* n_19 = IupHbox(n_20, n_21, nullptr);
Ihandle* n_23 = IupLabel("IUP: ");
Ihandle* n_24 = IupLabel(nullptr);
Ihandle* n_22 = IupHbox(n_23, n_24, nullptr);
Ihandle* n_26 = IupLabel("cxxopts: ");
Ihandle* n_27 = IupLabel(nullptr);
Ihandle* n_25 = IupHbox(n_26, n_27, nullptr);
Ihandle* n_29 = IupLabel("nlohmann::json: ");
Ihandle* n_30 = IupLabel(nullptr);
Ihandle* n_28 = IupHbox(n_29, n_30, nullptr);
Ihandle* n_0 = IupVbox(n_1, n_17, n_18, n_19, n_22, n_25, n_28, nullptr);

// Attribute section
IupSetAttribute(n_2, "IMAGE", "AAAAA");
IupSetAttribute(n_17, "SEPARATOR", "horizontal");

// Name section
IupSetHandle("about_version", n_7);
IupSetHandle("about_date", n_10);
IupSetHandle("about_compiler", n_13);
IupSetHandle("about_license", n_16);
IupSetHandle("about_lib_mbedtls", n_21);
IupSetHandle("about_lib_iup", n_24);
IupSetHandle("about_lib_cxxopts", n_27);
IupSetHandle("about_lib_json", n_30);
return n_0;
}