#include "current/server.hpp"

#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "current/config.hpp"

namespace DIG {
namespace Server {

std::vector<Data::Server> list;

inline std::vector<std::string> split(const std::string& s, char delim) {
  std::vector<std::string> result;
  std::stringstream ss(s);
  std::string item;

  while (getline(ss, item, delim)) {
    result.push_back(item);
  }

  return result;
}

Err read() {
  auto filename =
      ((Config::instance.game / "patcher") / "server") / "serverlist.txt";
  if (!std::filesystem::exists(filename)) {
    return Err::FILE_DOES_NOT_EXISTS;
  }
  std::ifstream file(filename);
  if (!file.is_open()) {
    return Err::CAN_NOT_OPEN_FILE;
  }
  std::string line;
  list.clear();
  while (std::getline(file, line)) {
    auto content = split(line, '\t');
    if (content.size() != 3) {
      continue;
    }
    list.push_back({name : content[0], address : content[1]});
  }
  return Err::OK;
}

}  // namespace Server
}  // namespace DIG