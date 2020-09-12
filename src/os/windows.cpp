#include "os.hpp"

#include <cstring>
#include <stdlib.h>

namespace DIG {
namespace OS {

std::filesystem::path data_dir() {
  // Not best method, but works
  char* path = getenv("LOCALAPPDATA");
  if (path == nullptr || strlen(path) <= 0) {
    path = getenv("APPDATA");
  }
  if (path == nullptr || strlen(path) <= 0) {
    throw "Failed to get system path";
  }
  return std::filesystem::path(path) / "PW-Auto-Login";
}

}  // namespace OS
}  // namespace DIG