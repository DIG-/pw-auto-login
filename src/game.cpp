#include "game.hpp"

#include <fstream>
#include <sstream>
#include "crypto.hpp"
#include "current/config.hpp"
#include "os.hpp"

namespace DIG {
namespace Game {

Err login(const Data::Account& account) {
  auto& config = Config::instance;
  Err e = Err::OK;
  const auto element = config.game / "element";

  // Check if require ADM to launch game
  bool require_adm = false;
  {
    std::ofstream test(element / "patcher.ini",
                       std::ofstream::binary | std::ofstream::ate);
    require_adm = !test.good();
  }
  const bool use64 = account.use64.value_or(config.use64);

  // Get real password
  std::string password;
  {
    std::stringstream value(account.password);
    std::stringstream temp;
    e = Crypto::dencode(temp, value);
    if (e != Err::OK)
      return e;
    value.str("");
    e = Crypto::decrypt(value, temp, account.key);
    if (e != Err::OK)
      return e;
    password = value.str();
  }

  if (config.allow_server && account.server.has_value()) {
    // TODO: Select server
  }

  std::stringstream command_params;
  command_params << config.command_line;
  command_params << " " << account.command_line;
  command_params << " user:" << account.username;
  command_params << " pwd:" << password;
  command_params << " role:" << account.character;

  auto path = element;
  auto executable = element / "elementclient.exe";
  if (use64) {
    executable = element / "elementclient_64.exe";
  }

  return OS::launch(require_adm, executable, path, command_params.str(),
                    account.character);
}

}  // namespace Game
}  // namespace DIG