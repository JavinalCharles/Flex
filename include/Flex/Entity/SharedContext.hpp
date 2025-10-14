#pragma once

#include "Flex/Event/EventManager.hpp"

namespace Flex {

struct SharedContext {
    EventManager* eventManager = nullptr;
}; // struct SharedContext

} // namespace Flex