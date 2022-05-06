#include "os.hpp"

#include <stdlib.h>
#include <windows.h>
#include <cstring>
#include <iostream>
#include "current/config.hpp"
#include "current/store.hpp"
#include "objbase.h"
#include "objidl.h"
#include "shlguid.h"
#include "shobjidl.h"

namespace DIG {
namespace OS {

std::filesystem::path data_dir() noexcept(false) {
  // Not best method, but works
  char* path = getenv("LOCALAPPDATA");
  if (path == nullptr || strlen(path) <= 0) {
    path = getenv("APPDATA");
  }
  if (path == nullptr || strlen(path) <= 0) {
    throw Err::FAILED_TO_GET_APPDATA_FOLDER;
  }
  auto context = std::filesystem::path(path) / "DIG";
  return context / "PW-Auto-Login";
}

std::string safe_name(const std::string& name) {
  std::string output = name;
  std::replace(output.begin(), output.end(), ':', '_');
  std::replace(output.begin(), output.end(), '\\', '_');
  std::replace(output.begin(), output.end(), '/', '_');
  std::replace(output.begin(), output.end(), '|', '_');
  std::replace(output.begin(), output.end(), '?', '_');
  std::replace(output.begin(), output.end(), '*', '_');
  std::replace(output.begin(), output.end(), '"', '_');
  std::replace(output.begin(), output.end(), '<', '_');
  std::replace(output.begin(), output.end(), '>', '_');
  return output;
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
           const std::filesystem::path& executable_,
           const std::filesystem::path& workdir_,
           const std::string& params,
           const std::string& window_title) {
  std::string executable = executable_.string();
  std::string workdir = workdir_.string();
  SHELLEXECUTEINFO sei = {0};
  sei.cbSize = sizeof(SHELLEXECUTEINFO);
  sei.fMask = SEE_MASK_NOCLOSEPROCESS;
  sei.hwnd = nullptr;
  sei.lpVerb = require_adm ? "runas" : "open";
  sei.lpFile = executable.c_str();
  sei.lpParameters = params.c_str();
  sei.lpDirectory = workdir.c_str();
  sei.nShow = SW_SHOWNORMAL;
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

Err create_link(const Data::Account& account) {
  auto& config = Config::instance;
  auto index = AccountStore::get_index();

  HRESULT hres;
  IShellLink* psl;
  CoInitialize(nullptr);
  hres = CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER,
                          IID_IShellLink, (LPVOID*)&psl);
  if (SUCCEEDED(hres)) {
    IPersistFile* ppf;

    // Set the path to the shortcut target and add the description.
    TCHAR szFileName[MAX_PATH];
    GetModuleFileName(NULL, szFileName, MAX_PATH);
    std::string arguments = std::string("-s ") + std::to_string(index) +
                            std::string(" -c ") + account.character;
    std::string description = account.character + " - Login";
    psl->SetPath(szFileName);
    psl->SetArguments(arguments.c_str());
    psl->SetDescription((description).c_str());

    // Query IShellLink for the IPersistFile interface, used for saving the
    // shortcut in persistent storage.
    hres = psl->QueryInterface(IID_IPersistFile, (LPVOID*)&ppf);

    if (SUCCEEDED(hres)) {
      WCHAR wsz[MAX_PATH];

      // Ensure that the string is Unicode.
      std::filesystem::path user_profile = getenv("USERPROFILE");
      std::string output =
          ((user_profile / "Desktop") / (safe_name(account.character) + ".lnk"))
              .string();
      MultiByteToWideChar(CP_ACP, 0, output.c_str(), -1, wsz, MAX_PATH);

      // Add code here to check return value from MultiByteWideChar
      // for success.

      // Save the link by calling IPersistFile::Save.
      hres = ppf->Save(wsz, TRUE);
      ppf->Release();
      psl->Release();
      return Err::OK;
    }
    psl->Release();
  }

  return Err::NOT_IMPLEMENTED;
}

}  // namespace OS
}  // namespace DIG