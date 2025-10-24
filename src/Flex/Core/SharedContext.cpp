#include "Flex/Core/SharedContext.hpp"
#include "Flex/Events/EventManager.hpp"
#include "Flex/Scenes/SceneManager.hpp"
#include "Flex/Window/Window.hpp"

using namespace Flex;

// SharedContext::SharedContext() = default;

// SharedContext::SharedContext(const SharedContext& other) :
//     eventManager(other.eventManager),
//     sceneManager(other.sceneManager),
//     window(other.window)
// {
    
// }

SharedContext& SharedContext::operator=(const SharedContext& other) {
    if (this == &other)
        return *this;
    this->eventManager = other.eventManager;
    this->sceneManager = other.sceneManager;
    this->window = other.window;
    
    return *this;
}
