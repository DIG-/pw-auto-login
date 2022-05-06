#include <iostream>

#include "crypto.hpp"
#include "current/config.hpp"
#include "data/account.hpp"
#include "data/store.hpp"
#include "error.hpp"
#include "game.hpp"
#include "os.hpp"
#include "store.hpp"
#include "ui.hpp"

#include <cxxopts.hpp>

int main(int argc, char** argv) {
  cxxopts::Options options("PW-Auto-Login",
                           "Simple creative Perfect World launcher");
  // clang-format off
  options.add_options()
  //        ("config-file","Config file (optional)",cxxopts::value<std::string>(),"FILE")
          ("s,account-store","Index of account-store in config file",cxxopts::value<int>(),"INDEX")
          ("account-store-file","Account-store file to be used",cxxopts::value<std::string>(),"FILE")
          ("account-store-password","Account-store password",cxxopts::value<std::string>(),"PASSWORD")
          ("a,account","Index of account inside account-store to be logged",cxxopts::value<int>(),"INDEX")
          ("c,character","Character with account inside account-store to be logged",cxxopts::value<std::string>(),"NAME")
          ;
  // clang-format on

  auto result = options.parse(argc, argv);
  if (result.count("account") + result.count("character") > 1) {
    DIG::UI::show_error_message("Only one account per shortcut");
    return 1;
  } else if (result.count("account") + result.count("character") == 1) {
    DIG::Data::AccountStoreInfo info;
    DIG::Config::init();
    if (result.count("account-store-file")) {
      info.file = result["account-store-file"].as<std::string>();
    } else if (result.count("account-store")) {
      auto index = result["account-store"].as<int>();
      if (index < 0 || index >= DIG::Config::instance.stores.size()) {
        DIG::UI::show_error_message(
            std::string("Can not found AccountStore by index #") +
            std::to_string(index));
        return 1;
      }
      info = DIG::Config::instance.stores[index];
    } else {
      DIG::UI::show_error_message(std::string("Require AccountStore"));
      return 1;
    }
    if (result.count("account-store-password")) {
      info.key = result["account-store-password"].as<std::string>();
    }

    if (!std::filesystem::exists(info.file)) {
      DIG::UI::show_error_message(
          std::string("Can not found AccountStore file: ") +
          info.file.string());
      return 1;
    }
    if (info.key.empty()) {
      DIG::UI::show_error_message(
          "AccountStore requires password, use parameter "
          "--account-store-password");
    }

    DIG::Data::AccountStore store = DIG::AccountStore::read(info);
    auto account = store.accounts.begin();
    if (result.count("account") == 1) {
      auto index = result["account"].as<int>();
      if (index < 0 || index >= store.accounts.size()) {
        DIG::UI::show_error_message(
            std::string("Can not found account #") + std::to_string(index) +
            std::string(" in AccountStore: ") + info.file.string());
        return 1;
      }
    } else {
      auto character = result["character"].as<std::string>();
      account = std::find_if(store.accounts.begin(), store.accounts.end(),
                             [&character](DIG::Data::Account& account) -> bool {
                               return character.compare(account.character) == 0;
                             });
      if (account == store.accounts.end()) {
        DIG::UI::show_error_message(
            std::string("Can not found character ") + character +
            std::string(" in AccountStore: ") + info.file.string());
        return 1;
      }
    }

    auto e = DIG::Game::login(*account);
    if (e != DIG::Err::OK) {
      DIG::UI::show_game_launch_error(e);
    }

    return 0;
  }

  DIG::UI::initialize();
  DIG::UI::run_main();
  DIG::UI::destroy();
  return 0;
}