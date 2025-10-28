#pragma once

#include <SFML/Window/Event.hpp>
#include <SFML/System/Vector2.hpp>
#include "Flex/Events/Types/Event.hpp"
#include "Flex/Utilities//Utility.hpp"

namespace Flex {
	struct MouseButtonPressedEvent : public Event<MouseButtonPressedEvent> {
		ID_t			button{};
		sf::Vector2i 	position{};

		constexpr MouseButtonPressedEvent() : Event<MouseButtonPressedEvent>()
		{ }
		constexpr MouseButtonPressedEvent(ID_t i_button, const sf::Vector2i& pos) : 
			Event<MouseButtonPressedEvent>(), button(i_button), position(pos)
		{ }
		constexpr MouseButtonPressedEvent(ID_t button, int x, int y) : 
			Event<MouseButtonPressedEvent>(), button(button), position(x, y)
		{ }
		constexpr explicit MouseButtonPressedEvent(const sf::Event::MouseButtonPressed& sfe) : 
			Event<MouseButtonPressedEvent>(),
			button(static_cast<ID_t>(sfe.button)),
			position(sfe.position)
		{ }
	}; // struct MouseButtonPressedEvent


	struct MouseButtonReleasedEvent : public Event<MouseButtonReleasedEvent> {
		ID_t			button{};
		sf::Vector2i 	position{};

		constexpr MouseButtonReleasedEvent() : Event<MouseButtonReleasedEvent>()
		{ }
		constexpr MouseButtonReleasedEvent(ID_t i_button, const sf::Vector2i& pos) : 
			Event<MouseButtonReleasedEvent>(), button(i_button), position(pos)
		{ }
		constexpr MouseButtonReleasedEvent(ID_t button, int x, int y) : 
			Event<MouseButtonReleasedEvent>(), button(button), position(x, y)
		{ }
		constexpr MouseButtonReleasedEvent(const sf::Event::MouseButtonReleased& sfe) : 
			Event<MouseButtonReleasedEvent>(),
			button(static_cast<ID_t>(sfe.button)),
			position(sfe.position)
		{ }
	}; // struct MouseButtonReleasedEvent


	struct MouseWheelScrolledEvent : public Event<MouseWheelScrolledEvent> {
		ID_t 			wheel{};
		float			delta{};
		sf::Vector2i 	position{};

		constexpr MouseWheelScrolledEvent() : Event<MouseWheelScrolledEvent>() { }
		constexpr MouseWheelScrolledEvent(ID_t i_wheel, float dt, const sf::Vector2i& pos) :
			Event<MouseWheelScrolledEvent>(),
			wheel(i_wheel), delta(dt), position(pos)
		{ }
		constexpr MouseWheelScrolledEvent(const sf::Event::MouseWheelScrolled& sfe) :
			Event<MouseWheelScrolledEvent>(),
			wheel(static_cast<ID_t>(sfe.wheel)),
			delta(sfe.delta),
			position(sfe.position)
		{ }
	};
} // namespace Flex