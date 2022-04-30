#include <iostream>

#include "config/config.hpp"
#include "crypto.hpp"
#include "data/account.hpp"
#include "error.hpp"
#include "os.hpp"
#include "ui.hpp"

#include <cxxopts.hpp>

int main(int argc, char** argv) {
  cxxopts::Options options("PW-Auto-Login",
                           "Simple creative Perfect World launcher");
  // clang-format off
  options.add_options()
          ("config-file","Config file (optional)",cxxopts::value<std::string>(),"FILE")
          ("s,account-store","Index of account-store in config file",cxxopts::value<int>(),"INDEX")
          ("account-store-file","Account-store file to be used",cxxopts::value<std::string>(),"FILE")
          ("a,account","Index of account inside account-store to be logged",cxxopts::value<int>(),"INDEX")
          ;
  // clang-format on

  auto result = options.parse(argc, argv);
  if (result.count("account") > 1) {
    DIG::UI::show_error_message("Only one account per shortcut");
    return 1;
  } else if (result.count("account") == 1) {
    // TODO: Login
    return 0;
  }

  std::cout << "Initialize UI" << std::endl;
  return 0;
}