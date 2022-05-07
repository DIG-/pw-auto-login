#ifndef COMPILER_NAME

#ifdef __clang__
constexpr const char* COMPILER_NAME = __VERSION__;
#elif defined __ICC
constexpr const char* COMPILER_NAME = __VERSION__;
#elif defined __GNUG__
constexpr const char* COMPILER_NAME = "GNU GCC " __VERSION__;
#elif defined __HP_aCC
constexpr const char* COMPILER_NAME = "HP Compiler " __HP_aCC;
#elif defined __IBMCPP__
constexpr const char* COMPILER_NAME = "IBM XL C++ " __xlc__;
#elif defined _MSC_VER
constexpr const char* COMPILER_NAME = "Micro$oft Visual Studio " _MSC_VER;
#elif defined __SUNPRO_CC
constexpr const char* COMPILER_NAME = "Oracle Solaris Studio " __SUN_PRO_CC;
#elif defined __PGIC__
constexpr const char* COMPILER_NAME =
    "Portland Group " __PGIC__ "." __PGIC_MINOR__ "." __PGIC_PATCHLEVEL__;
#else
constexpr const char* COMPILER_NAME = "Unknown compiler";
#endif

#if (defined(__i386) || defined(__i386__) || defined(_M_IX86))
constexpr const char* PLATAFORM = "32 bits";
#else
constexpr const char* PLATAFORM = "64 bits";
#endif

#endif
