#pragma once

#include <memory>
#include <unordered_map>
#include <vector>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

#include "Flex/Events/EventHandler.hpp"

namespace Flex {

template <typename T>
concept EventHandlerType = std::derived_from<EventHandler, T>;

class EventManager {
public:

    EventManager();
    EventManager(const EventManager&) = delete;
    EventManager(EventManager&&) = delete;
    EventManager& operator=(const EventManager&) = delete;
    EventManager& operator=(EventManager&&) = delete;
    virtual ~EventManager();

    template <EventHandlerType E>
    [[nodiscard]] bool hasEventHandler() const {
        return m_eventHandlers.contains(std::type_index(typeid(E)));
    }

    template <EventType T>
    [[nodiscard]] bool hasEventHandlerForEvent() const {
        return m_eventToHandlerMap.contains(std::type_index(typeid(T)));
    }

    template <EventHandlerType E>
    [[nodiscard]] std::shared_ptr<EventHandler> getEventHandler() const {
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

    template <EventType ET>
    void handleEvent(const ET& event) {
        const std::type_index& eventID = std::type_index(typeid(ET));
        try {
            m_eventHandlers.at(m_eventToHandlerMap.at(std::type_index(typeid(ET))))->handleEvent(event);
        }
        catch (const std::out_of_range& e) {
            std::cerr << "std::out_of_range caught at EventManager::handleEvent: \"" << e.what() << "\"" << std::endl;
        }
    }
private:
    std::unordered_map<std::type_index, std::type_index> m_eventToHandlerMap{};
    std::unordered_map<std::type_index, std::shared_ptr<EventHandler>> m_eventHandlers{};
}; // class EventManager

} // namespace Flex