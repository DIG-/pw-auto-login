#include "current/server.hpp"

#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "current/config.hpp"
#include "os.hpp"

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

inline std::vector<std::wstring> split(const std::wstring& s, wchar_t delim) {
  std::vector<std::wstring> result;
  std::wstringstream ss(s);
  std::wstring item;

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
  std::ifstream file(filename, std::fstream::binary);
  if (!file.is_open()) {
    return Err::CAN_NOT_OPEN_FILE;
  }
  file.seekg(0, std::fstream::end);
  size_t size = (size_t)file.tellg();

  // skip BOM
  file.seekg(2, std::fstream::beg);
  size -= 2;

  std::wstring u16((size / 2) + 1, '\0');
  file.read((char*)&u16[0], size);

  std::string utf8 = OS::narrow(u16);
  std::stringstream converted(utf8);
  std::string line;
  list.clear();
  while (std::getline(converted, line)) {
    auto content = split(line, '\t');
    if (content.size() != 3) {
      continue;
    }
    list.push_back(Data::Server{content[0], content[1]});
  }
  return Err::OK;
}

}  // namespace Server
}  // namespace DIG