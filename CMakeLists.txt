cmake_minimum_required(VERSION 3.1)
project(pw-auto-login CXX)
set(VERSION_MAJOR 0)
set(VERSION_MINOR 1)
set(VERSION_PATCH 0)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(LIBIUP REQUIRED)
find_package(MbedTLS REQUIRED)
find_package(Filesystem REQUIRED)
find_package(nlohmann_json REQUIRED)
find_package(cxxopts REQUIRED)

option(DISABLE_ENCRYPT "Disable crypto" OFF)

configure_file(res/app.i.rc res/app.rc)
if (CMAKE_SIZEOF_VOID_P EQUAL "8")
  configure_file(res/app64.i.manifest res/app.manifest)
else()
  configure_file(res/app32.i.manifest res/app.manifest)
endif()

add_executable(pw-auto-login WIN32)
set_target_properties(pw-auto-login PROPERTIES
            CXX_STANDARD 17
)
target_include_directories(pw-auto-login PRIVATE hdr)
target_include_directories(pw-auto-login PRIVATE ${LIBIUP_INCLUDE_DIR})
target_include_directories(pw-auto-login PRIVATE ${MBEDTLS_INCLUDE_DIR})
target_sources(pw-auto-login PRIVATE 
    res/app.rc
    src/main.cpp
    src/current/account.cpp
    src/current/config.cpp
    src/current/server.cpp
    src/current/store.cpp
    src/crypto.cpp
    src/data/account.cpp
    src/data/config.cpp
    src/data/server.cpp
    src/data/store.cpp
    src/game.cpp
    src/os/windows.cpp
    src/ui/account.cpp
    src/ui/main.cpp
    src/ui/prompt.cpp
    src/ui/settings.cpp
    src/ui/ui.cpp
    src/store.cpp
)
target_link_libraries(pw-auto-login ${LIBIUP_LIBRARIES})
target_link_libraries(pw-auto-login ${MBEDTLS_LIBRARIES})
target_link_libraries(pw-auto-login std::filesystem)
target_link_libraries(pw-auto-login nlohmann_json::nlohmann_json)
target_link_libraries(pw-auto-login cxxopts::cxxopts)

if (DISABLE_ENCRYPT)
  add_definitions(-DDISABLE_ENCRYPT)
endif()
