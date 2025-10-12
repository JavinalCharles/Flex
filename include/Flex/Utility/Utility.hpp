#pragma once

#include <cstdint>
#include <string>
#include <unordered_map>
#include <variant>

namespace Flex {

using configMap = std::unordered_map<std::
string, std::variant<int, double, std::string>>;

using ID8_t = std::uint_fast8_t;
using ID32_t = std::uint_fast32_t;
using ID16_t = std::uint_fast16_t;
using ID_t = ID32_t; // DEFAULT id type
} // namespace Flex