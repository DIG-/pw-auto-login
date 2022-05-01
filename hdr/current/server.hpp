#pragma once

#include <vector>
#include "data/server.hpp"
#include "error.hpp"

namespace DIG {
namespace Server {

extern std::vector<Data::Server> list;

Err read();

}  // namespace Server
}  // namespace DIG