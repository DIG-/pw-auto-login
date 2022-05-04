#include "os.hpp"

#include <stdlib.h>
#include <windows.h>
#include <cstring>

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
  auto context = std::filesystem::path(path) / "DIG";
  return context / "PW-Auto-Login";
}

struct ProcessWindowsInfo {
  DWORD ProcessID;
  std::vector<HWND> Windows;

  ProcessWindowsInfo(DWORD const AProcessID) : ProcessID(AProcessID) {}
};

BOOL __stdcall EnumProcessWindowsProc(HWND hwnd, LPARAM lParam) {
  ProcessWindowsInfo* Info = reinterpret_cast<ProcessWindowsInfo*>(lParam);
  DWORD WindowProcessID;

  GetWindowThreadProcessId(hwnd, &WindowProcessID);

  if (WindowProcessID == Info->ProcessID)
    Info->Windows.push_back(hwnd);

  return true;
}

Err launch(const bool require_adm,
           const std::filesystem::path& executable,
           const std::filesystem::path& workdir,
           const std::string& params,
           const std::string& window_title) {
  SHELLEXECUTEINFO sei = {0};
  sei.cbSize = sizeof(SHELLEXECUTEINFO);
  sei.fMask = SEE_MASK_NOCLOSEPROCESS;
  sei.hwnd = nullptr;
  sei.lpVerb = require_adm ? "runas" : "open";
  sei.lpFile = executable.string().c_str();
  sei.lpParameters = params.c_str();
  sei.lpDirectory = workdir.string().c_str();
  sei.nShow = SW_HIDE;
  sei.hInstApp = nullptr;
  if (ShellExecuteExA(&sei)) {
    if (window_title.empty()) {
      return Err::OK;
    }
    WaitForInputIdle(sei.hProcess, INFINITE);
    ProcessWindowsInfo Info(GetProcessId(sei.hProcess));
    EnumWindows((WNDENUMPROC)EnumProcessWindowsProc,
                reinterpret_cast<LPARAM>(&Info));
    for (auto& handle : Info.Windows) {
      SetWindowTextA(handle, window_title.c_str());
    }
    return Err::OK;
  }
  return Err::FAILED_TO_LAUNCH;
}

}  // namespace OS
}  // namespace DIG