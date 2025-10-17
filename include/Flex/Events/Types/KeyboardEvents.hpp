#pragma once

#include <type_traits>
#include "Flex/Events/Types/Event.hpp"

namespace Flex {
	enum KeyEventMod {
		NO_MOD 		= 0,
		ALT_MOD 	= 0b1,
		CTRL_MOD 	= 0b10,
		SHIFT_MOD 	= 0b100,
		SYSTEM_MOD	= 0B1000
	};

	template <typename T>
	concept SF_KEY_EVENT = std::is_same_v<T, sf::Event::KeyPressed> || std::is_same_v<T, sf::Event::KeyReleased>;

	template <SF_KEY_EVENT>
	struct KeyboardEvent : public Events<KeyboardEvent<SF_KEYEVENT>> {
		ID_t			code{};
		ID_t			scancode{};
		std::uint8_t 	modifiers{};

		KeyboardEvent() : 
			Event<KeyboardEvent<SF_KEY_EVENT>>() {}
		KeyboardEvent(ID_t code, ID_t scancode, std::uint8_t modifiers) :
			Event<KeyboardEvent<SF_KEY_EVENT>>(),
			code(code), scancode(scancode), modifiers(modifiers)
		{ }
		KeyboardEvent(const T& e) :
			Event<KeyboardEvent<T>>(),
			code(static_cast<ID_t>(e.code)),
			scancode(static_cast<ID_t>(e.scancode)),
			modifiers(
				(e.alt ? ALT_MOD : NO_MOD) | 
				(e.control ? CTRL_MOD : NO_MOD) |
				(e.shift ? SHIFT_MOD : NO_MOD) |
				(e.system ? SYSTEM_MOD : NO_MOD))
		{ }

		std::string message() const {
			return std::string("[") + std::to_string(code) + "; " + std::string(scancode) + ": " + std::string(modifiers) + "]";
		}
	}; // struct KeyboardEvent

	using KeyPressedEvent = KeyboardEvent<sf::Event::KeyPressed>;
	using KeyReleasedEvent = KeyboardEvent<sf::Event::KeyReleased>;
} // namespace Flex