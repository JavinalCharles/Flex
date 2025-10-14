#pragma once

#include <memory>
#include <unordered_map>
#include <vector>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

#include "Flex/Event/EventHandler.hpp"

namespace Flex {

template <typename E>
concept EventHandlerType = std::derived_from<EventHandler, E>;

class EventManager {
public:
    EventManager();
    EventManager(const EventManager&) = delete;
    EventManager(EventManager&&) = delete;
    EventManager& operator=(const EventManager&) = delete;
    EventManager& operator=(EventManager&&) = delete;
    virtual ~EventManager();

    template <EventHandlerType E>
    std::shared_ptr<EventHandler> getEventHandler() const {
        std::type_index index(typeid(E));
        if (m_eventHandlers.contains(index)) {
            return m_eventHandlers.at(index);
        }
        return nullptr;
    }

    template <EventHandlerType E>
    std::shared_ptr<EventHandler> addEventHandler() {
        std::type_index index(typeid(E));
        if (m_eventHandlers.contains(index))
            return m_eventHandlers.at(index);

        std::shared_ptr<EventHandler> handler = std::make_shared<E>();
        if )(handler == nullptr) 
            return nullptr;

        for (const auto& eventType : handler->getEventTypes()) {
            m_eventToHandlerMap[eventType] = index;
        }
        m_eventHandlers[index] = handler;
        return handler;
    }

    void handleEvents(sf::RenderWindow& window);
private:
    std::unordered_map<std::type_index, std::type_index> m_eventToHandlerMap{};
    std::unordered_map<std::type_index, std::shared_ptr<EventHandler>> m_eventHandlers{};
}; // class EventManager

} // namespace Flex