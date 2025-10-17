#pragma once

#include <type_traits>
#include <SFML/Window/Event.hpp>
#include <SFML/System/Vector2.hpp>
#include "Flex/Events/Types/Event.hpp"

namespace Flex {
	template <typename T>
	concept SF_MOUSE_BUTTON_EVENT = 
		std::is_same_v<T, sf::Event::MouseButtonPressed> ||
		std::is_same_v<T, sf::Event::MouseButtonReleased>;

	template <SF_MOUSE_BUTTON_EVENT T>
	struct MouseButtonEvent : public Event<MouseButtonEvent<T>> {
		ID_t 		button{};
		sf::Vector2i	position{};

		MouseButtonEvent() : Event<MouseButtonEvent<T>>() {}

		MouseButtonEvent(ID_t btn, const Vector2i& pos) : 
			Event<MouseButtonEvent<T>>(),
			button(btn),
			position(pos)
		{ }

		MouseButtonEvent(const T& e) :
			Event<MouseButtonEvent<T>>(),
			button(e.button),
			position(e.position)
		{ }

		std::string message() const {
			return std::string("[") + std::to_string(button) + "; (" + std::to_string(position.x) + ", " + std::to_string(position.y) + ")]";
		}
	}; // struct MouseButtonEvent

	struct MouseWheelScrolledEvent : public Event<MouseWheelScrolledEvent> {
		ID_t 			wheel{};
		float			delta{};
		sf::Vector2i 	position{};

		MouseWheelScrolledEvent();
		// MouseWheelScrolledEvent(ID_t wheel, float delta, const sf::Vector2i& pos);
		MouseWheelScrolledEvent(const sf::Event::MouseWheelScrolled& e);

		std::string message() const;
	}; // struct MouseWheelScrolled

	using MouseButtonPressedEvent = MouseButtonEvent<sf::Event::MouseButtonPressed>;
	using MouseButtonReleasedEvent = MouseButtonEvent<sf::Event::MouseButtonReleased>;
} // namespace Flex