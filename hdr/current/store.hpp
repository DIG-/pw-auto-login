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
Err open_first();
uint_fast16_t get_index();
Err save();

}  // namespace AccountStore
}  // namespace DIG