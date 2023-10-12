#include "game.hpp"

#include <codecvt>
#include <fstream>
#include <sstream>

#include "crypto.hpp"
#include "current/config.hpp"
#include "os.hpp"

namespace DIG {
namespace Game {

Err utf8_to_utf16le(std::stringstream& output, const std::string& input) {
  auto utf16 =
      std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t>{}
          .from_bytes(input);
  for (auto& c : utf16) {
    output.write((char*)&c, 2);
  }
  return Err::OK;
}

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
    std::stringstream encoded(account.password);
    std::stringstream encrypted;
    e = Crypto::dencode(encrypted, encoded);
    if (e != Err::OK) return e;
    std::stringstream plain;
    e = Crypto::decrypt(plain, encrypted, account.key);
    if (e != Err::OK) return e;
    password = plain.str();
  }

  if (config.allow_server && account.server.has_value()) {
    if (require_adm) {
      return Err::REQUIRE_ADMIN;
    }
    // TODO: Select server
    std::string line;
    {
      std::stringstream encoded;
      std::stringstream t1;
      utf8_to_utf16le(t1, account.username);
      Crypto::encode(encoded, t1);
      encoded << " ";
      std::stringstream t2;
      utf8_to_utf16le(t2, account.server.value().address + std::string(",") +
                              account.server.value().name + ",0");
      Crypto::encode(encoded, t2);
      line = encoded.str();
    }
    const auto accounts_filename = (element / "userdata") / "accounts.txt";
    std::fstream output(accounts_filename, std::ios::in | std::ios::out);
    char buffer[5] = {0};
    output.read(buffer, 4);
    if (std::string("true").compare(buffer) != 0) {
      output.close();
      output.open(accounts_filename, std::ios::out | std::ios::trunc);
      output << "true" << std::endl;
    } else {
      output.seekp(0, std::ios::end);
    }
    output << line << std::endl;
    if (!output.good()) {
      return Err::FAILED_TO_SELECT_SERVER;
    }
    output.close();
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
    path = path / "x64";
    executable = path / "elementclient_64.exe";
  }

  return OS::launch(require_adm, executable, path,
                    std::optional<std::filesystem::path>(),
                    command_params.str(), account.character);
}

}  // namespace Game
}  // namespace DIG