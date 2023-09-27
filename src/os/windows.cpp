#include "os.hpp"

#include <objbase.h>
#include <objidl.h>
#include <propkey.h>
#include <propvarutil.h>
#include <shlguid.h>
#include <shobjidl.h>
#include <stdlib.h>
#include <windows.h>

#include <algorithm>
#include <codecvt>
#include <cstring>
#include <iostream>

#include "crypto.hpp"
#include "current/config.hpp"
#include "current/store.hpp"

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

std::wstring convert_to_widen(const std::string&& narrow) {
  const std::size_t size = 2 * narrow.size();
  wchar_t buffer[size];
  MultiByteToWideChar(CP_ACP, 0, narrow.c_str(), -1, buffer, size);
  return std::wstring(buffer);
}

Err launch(const bool require_adm,
           const std::filesystem::path& executable_,
           const std::filesystem::path& workdir_,
           const std::filesystem::path& icon,
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
    if (window_title.empty() && icon.empty()) {
      return Err::OK;
    }
    WaitForInputIdle(sei.hProcess, INFINITE);
    ProcessWindowsInfo Info(GetProcessId(sei.hProcess));
    EnumWindows((WNDENUMPROC)EnumProcessWindowsProc,
                reinterpret_cast<LPARAM>(&Info));
    IPropertyStore* pps;

    std::wstring window_id;
    HICON window_icon = 0;
    if (icon.empty()) {
      // Nothing to do
    } else if (icon.is_relative() && !icon.has_extension()) {
      window_icon = LoadIcon(GetModuleHandle(nullptr), icon.string().c_str());
      window_id = convert_to_widen("pw-auto-window-" + Crypto::random(32));
    } else {
      window_icon = reinterpret_cast<HICON>(
          LoadImageW(nullptr, icon.c_str(), IMAGE_ICON, 0, 0,
                     LR_DEFAULTSIZE | LR_LOADFROMFILE | LR_SHARED));
      window_id = convert_to_widen("pw-auto-window-" + Crypto::random(32));
    }

    for (auto& handle : Info.Windows) {
      if (!window_title.empty()) {
        SetWindowTextA(handle, window_title.c_str());
      }
      if (window_icon != 0) {
        SendMessage(handle, WM_SETICON, ICON_SMALL,
                    reinterpret_cast<LPARAM>(window_icon));
        SendMessage(handle, WM_SETICON, ICON_BIG,
                    reinterpret_cast<LPARAM>(window_icon));
        if (SUCCEEDED(
                SHGetPropertyStoreForWindow(handle, IID_PPV_ARGS(&pps)))) {
          PROPVARIANT prop;
          InitPropVariantFromString(window_id.c_str(), &prop);
          pps->SetValue(PKEY_AppUserModel_ID, prop);
          pps->Release();
        }
      }
    }
    return Err::OK;
  }
  return Err::FAILED_TO_LAUNCH;
}

Err create_link(const Data::Account& account) {
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