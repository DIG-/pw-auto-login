#pragma once

#include <filesystem>
#include "data/account.hpp"
#include "data/config.hpp"
#include "data/store.hpp"
#include "error.hpp"

namespace DIG {
namespace AccountStore {

extern Data::AccountStore instance;

Err open(const std::filesystem::path&, const std::string&);
Err open(const Data::AccountStoreInfo&);

}  // namespace AccountStore
}  // namespace DIG