#pragma once

#include <filesystem>
#include "data/account.hpp"
#include "data/config.hpp"
#include "data/store.hpp"

namespace DIG {
namespace AccountStore {

Data::AccountStore open(const std::filesystem::path&, const std::string&);
Data::AccountStore open(const Data::AccountStoreInfo&);

}  // namespace AccountStore
}  // namespace DIG
