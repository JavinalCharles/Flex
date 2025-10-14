#pragma once

#include "Flex/Events/EventManager.hpp"

namespace Flex {

struct SharedContext {
    EventManager* eventManager = nullptr;
}; // struct SharedContext

} // namespace Flex