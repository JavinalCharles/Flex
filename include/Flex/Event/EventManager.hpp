#pragma once

#include <memory>
#include <unordered_map>
#include <vector>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

#include "Flex/Event/EventHandler.hpp"

namespace Flex {

class EventManager {
public:
    EventManager();
    EventManager(const EventManager&) = delete;
    EventManager(EventManager&&) = delete;
    EventManager& operator=(const EventManager&) = delete;
    EventManager& operator=(EventManager&&) = delete;
    virtual ~EventManager();

    void addEventHandler(std::shared_ptr<EventHandler> handler);

    void handleEvents(const sf::RenderWindow& window);
private:
    std::vector<std::shared_ptr<EventManager>> m_eventHandlers;
}; // class EventManager

} // namespace Flex