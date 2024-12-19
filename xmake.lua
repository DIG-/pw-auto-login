add_rules("mode.debug", "mode.release")

add_repositories("dig-repo https://github.com/DIG-/cpp-xrepo.git")

add_requires("cxxopts ^3.0.0")
add_requires("libiup ^3.30")
add_requires("mbedtls ^2.16.2", {configs={shared=true}})
add_requires("nlohmann_json ^3.10.5")

target("pw-auto-login")
    set_kind("binary")
    set_version("0.2.2")
    set_warnings("all")
    set_languages("cxx17")

    add_packages("cxxopts")
    add_packages("mbedtls")
    add_packages("nlohmann_json")
    add_packages("libiup")

    add_syslinks("ole32")
    add_syslinks("uuid")
    add_ldflags("-mwindows")
    
    add_includedirs("hdr")
    add_includedirs("$(buildir)/hdr")

    set_configvar("PROJECT_ROOT", "$(projectdir)")
    add_configfiles("(hdr/version.i.hpp)", {filename="version.hpp"})
    add_configfiles("(res/app.i.rc)", {filename="app.rc"})

    add_files("src/*.cpp")
    add_files("src/current/*.cpp")
    add_files("src/data/*.cpp")
    add_files("src/os/*.cpp")
    add_files("src/ui/*.cpp")
    add_files("$(buildir)/res/app.rc")

    on_load(function (target)
        if target:is_arch("x86") then 
            target:add("configfiles", "(res/app32.i.manifest)", {filename="app.manifest"})
        else
            target:add("configfiles", "(res/app64.i.manifest)", {filename="app.manifest"})
        end
    end)