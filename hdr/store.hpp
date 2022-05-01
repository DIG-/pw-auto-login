#pragma once

#include <filesystem>
#include "data/account.hpp"
#include "data/config.hpp"
#include "data/store.hpp"

namespace DIG {
namespace AccountStore {

Data::AccountStore read(const std::filesystem::path&, const std::string&);
Data::AccountStore read(const Data::AccountStoreInfo&);

}  // namespace AccountStore
}  // namespace DIG
