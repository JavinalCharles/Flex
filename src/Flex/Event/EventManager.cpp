#include "Flex/Event/EventManager.hpp"

using Flex::EventHandler;
using Flex::EventManager;

EventManager::EventManager() = default;

EventManager::~EventManager() = default;

void EventManager::handleEvents(sf::RenderWindow& window) {
    while (const std::optional<sf::Event> event = window.pollEvent()) {
        std::type_index eventID = event->visit([](auto&& arg) -> std::type_index {

            return std::type_index(typeid(std::decay_t<decltype(arg)>));
        });

        if (m_eventToHandlerMap.contains(eventID)) {
            std::type_index handlerIndex = m_eventToHandlerMap.at(eventID);
            if (m_eventHandlers.contains(handlerIndex)) {
                m_eventHandlers.at(handlerIndex)->handleEvent(*event);
            }
        }
    }
}