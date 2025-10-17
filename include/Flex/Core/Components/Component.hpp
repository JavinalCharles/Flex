#pragma once

#include <concepts>

#include "Flex/Utilities/Utility.hpp"

namespace Flex {

class Component {
public:
	
}; // class Component

template <typename C>
concept ComponentType = std::derived_from<C, Component>;

} // namespace Flex