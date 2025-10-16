#pragma once

#include <typeindex>
#include <vector>
#include <SFML/Window/Event.hpp>

#include "Flex/Utilities/Utility.hpp"

namespace Flex {

template<typename T>
concept EventType = 
	std::is_same_v<T, sf::Event::Closed> ||
	std::is_same_v<T, sf::Event::FocusGained> ||
	std::is_same_v<T, sf::Event::FocusLost> ||
	std::is_same_v<T, sf::Event::JoystickButtonPressed> ||
	std::is_same_v<T, sf::Event::JoystickButtonReleased> ||
	std::is_same_v<T, sf::Event::JoystickConnected> ||
	std::is_same_v<T, sf::Event::JoystickDisconnected> ||
	std::is_same_v<T, sf::Event::JoystickMoved> ||
	std::is_same_v<T, sf::Event::KeyPressed> ||
	std::is_same_v<T, sf::Event::KeyReleased> ||
	std::is_same_v<T, sf::Event::MouseButtonPressed> ||
	std::is_same_v<T, sf::Event::MouseButtonReleased> ||
	std::is_same_v<T, sf::Event::MouseEntered> ||
	std::is_same_v<T, sf::Event::MouseLeft> ||
	std::is_same_v<T, sf::Event::MouseMoved> ||
	std::is_same_v<T, sf::Event::MouseMovedRaw> ||
	std::is_same_v<T, sf::Event::MouseWheelScrolled> ||
	std::is_same_v<T, sf::Event::Resized> ||
	std::is_same_v<T, sf::Event::SensorChanged> ||
	std::is_same_v<T, sf::Event::TextEntered> ||
	std::is_same_v<T, sf::Event::TouchBegan> ||
	std::is_same_v<T, sf::Event::TouchEnded> ||
	std::is_same_v<T, sf::Event::TouchMoved>;

class EventHandler {
public:
	EventHandler();
	EventHandler(const EventHandler&) = delete;
	EventHandler(EventHandler&&) = delete;
	EventHandler& operator=(const EventHandler&) = delete;
	EventHandler& operator=(EventHandler&&) = delete;
	virtual ~EventHandler();

	virtual std::vector<std::type_index> getEventTypes() const = 0;

	[[nodiscard]] virtual bool handleEvent(const sf::Event::JoystickButtonPressed& e);
	[[nodiscard]] virtual bool handleEvent(const sf::Event::JoystickButtonPressed& e);
	[[nodiscard]] virtual bool handleEvent(const sf::Event::JoystickButtonPressed& e);
	[[nodiscard]] virtual bool handleEvent(const sf::Event::JoystickButtonReleased& e);
	[[nodiscard]] virtual bool handleEvent(const sf::Event::JoystickConnected& e);
	[[nodiscard]] virtual bool handleEvent(const sf::Event::JoystickDisconnected e);
	[[nodiscard]] virtual bool handleEvent(const sf::Event::JoystickMoved e);
	[[nodiscard]] virtual bool handleEvent(const sf::Event::KeyPressed& e);
	[[nodiscard]] virtual bool handleEvent(const sf::Event::KeyReleased& e);
	[[nodiscard]] virtual bool handleEvent(const sf::Event::MouseButtonPressed& e);
	[[nodiscard]] virtual bool handleEvent(const sf::Event::MouseButtonReleased& e);
	[[nodiscard]] virtual bool handleEvent(const sf::Event::MouseEntered e);
	[[nodiscard]] virtual bool handleEvent(const sf::Event::MouseLeft& e);
	[[nodiscard]] virtual bool handleEvent(const sf::Event::MouseMoved& e);
	[[nodiscard]] virtual bool handleEvent(const sf::Event::MouseMovedRaw& e);
	[[nodiscard]] virtual bool handleEvent(const sf::Event::MouseWheelScrolled& e);
	[[nodiscard]] virtual bool handleEvent(const sf::Event::SensorChanged& e);
	[[nodiscard]] virtual bool handleEvent(const sf::Event::TextEntered& e);
	[[nodiscard]] virtual bool handleEvent(const sf::Event::TouchBegan& e);
	[[nodiscard]] virtual bool handleEvent(const sf::Event::TouchEnded& e);
	[[nodiscard]] virtual bool handleEvent(const sf::Event::TouchMoved& e);
}; //  class EventHandler

} // namespace Flex