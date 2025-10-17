#pragma once
#include <string>

#include <SFML/Window/Event.hpp>
#include "Flex/Utilities/Utility.hpp"

namespace Flex {
	template <typename Derived>
	struct Event {
		Event() = default;
		~Event() = default;

		static std::string_view eventName() {
			return std::string_view(typeid(Derived).name());
		}

		std::string log() const {
			return static_cast<Derived*>(this)->message();
		}
	}; // struct Event

	// A few basic Events
	enum KeyEventMod {
		NO_MOD 		= 0,
		ALT_MOD 	= 0b1,
		CTRL_MOD 	= 0b10,
		SHIFT_MOD 	= 0b100,
		SYSTEM_MOD	= 0B1000
	};

	struct KeyPressedEvent : public Event<KeyPressedEvent> {
		ID_t 				key{};
		ID_t 				scanCode{};
		std::uint8_t		modifiers{};

		KeyPressedEvent();
		KeyPressedEvent(const sf::Event::KeyPressed& e);
	}; // struct KeyPressedEvent;

	struct KeyReleasedEvent : public Event<KeyReleasedEvent> {
		ID_t			key{};
		ID_t			scanCode{};
		std::uint8_t 	modifiers{};

		KeyReleasedEvent();
		KeyReleasedEvent(const sf::Event::KeyReleased& e);
	}; // struct KeyReleasedEvent

	struct MouseButtonPressedEvent : public Event<MouseButtonPressedEvent> {
		ID_t			button{};
		sf::Vector2i	position{};

		MouseButtonPressedEvent();
		MouseButtonPressedEvent(const sf::Event::MouseButtonPressed& e);
	}; // struct MouseButtonPressedEvent

	struct MouseButtonReleasedEvent : public Event<MouseButtonReleasedEvent> {
		ID_t			button{};
		sf::Vector2i	position();

		MouseButtonReleasedEvent();
		MouseButtonReleasedEvent(const sf::Event::MouseButtonReleased& e);
	};

	struct MouseWheelScrolledEvent : public Event<MouseWheelScrolledEvent> {
		ID_t 			wheel{};
		float 			delta{};
		sf::Vector2i 	position{};

		MouseWheelScrolledEvent();
		MouseWheelScrolledEvent(const sf::Event::MouseWheelScrolled& e);
	};
} // namespace Flex