#pragma once

#include <filesystem>
#include "data/account.hpp"
#include "data/config.hpp"
#include "data/store.hpp"
#include "error.hpp"

namespace DIG {
namespace AccountStore {

Data::AccountStore read(const std::filesystem::path&, const std::string&);
Data::AccountStore read(const Data::AccountStoreInfo&);
Err read(Data::AccountStore&, const std::filesystem::path&, const std::string&);
Err read(Data::AccountStore&, const Data::AccountStoreInfo&);

Err save(const Data::AccountStore&,
         const std::filesystem::path&,
         const std::string&);
Err save(const Data::AccountStore&, const Data::AccountStoreInfo&);

}  // namespace AccountStore
}  // namespace DIG
