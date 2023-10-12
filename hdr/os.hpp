#pragma once

#include <optional>
#include <filesystem>
#include "data/account.hpp"
#include "error.hpp"

namespace DIG {
namespace OS {

std::filesystem::path data_dir() noexcept(false);
Err launch(const bool require_adm,
           const std::filesystem::path& executable,
           const std::filesystem::path& workdir,
           const std::optional<std::filesystem::path>& icon,
           const std::string& params,
           const std::string& window_title = "");
Err create_link(const Data::Account&);

}  // namespace OS
}  // namespace DIG