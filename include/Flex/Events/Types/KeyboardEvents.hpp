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

	struct KeyPressedEvent : public Event<KeyPressedEvent> {
		ID_t 			code{};
		ID_t			scancode{};
		std::uint8_t	modifiers{};

		constexpr KeyPressedEvent() : Event<KeyPressedEvent>() { }
		constexpr KeyPressedEvent(ID_t i_code, ID_t i_scancode, std::uint8_t mod) :
			Event<KeyPressedEvent>(),
			code(i_code), scancode(i_scancode), modifiers(mod)
		{ }
		constexpr KeyPressedEvent(const sf::Event::KeyPressed& sfe) :
			Event<KeyPressedEvent>(),
			code(static_cast<ID_t>(sfe.code)), scancode(static_cast<ID_t>(sfe.scancode)),
			modifiers(
				(sfe.alt ? ALT_MOD : NO_MOD) | 
				(sfe.control ? CTRL_MOD : NO_MOD) |
				(sfe.shift ? SHIFT_MOD : NO_MOD) |
				(sfe.system ? SYSTEM_MOD : NO_MOD)
			)
		{ }
	}; // struct KeyPressedEvent

	struct KeyReleasedEvent : public Event<KeyReleasedEvent> {
		ID_t 			code{};
		ID_t			scancode{};
		std::uint8_t	modifiers{};

		constexpr KeyReleasedEvent() : Event<KeyReleasedEvent>() { }
		constexpr KeyReleasedEvent(ID_t i_code, ID_t i_scancode, std::uint8_t mod) :
			Event<KeyReleasedEvent>(),
			code(i_code), scancode(i_scancode), modifiers(mod)
		{ }
		constexpr KeyReleasedEvent(const sf::Event::KeyReleased& sfe) :
			Event<KeyReleasedEvent>(),
			code(static_cast<ID_t>(sfe.code)), scancode(static_cast<ID_t>(sfe.scancode)),
			modifiers(
				(sfe.alt ? ALT_MOD : NO_MOD) | 
				(sfe.control ? CTRL_MOD : NO_MOD) |
				(sfe.shift ? SHIFT_MOD : NO_MOD) |
				(sfe.system ? SYSTEM_MOD : NO_MOD)
			)
		{ }
	}; // struct KeyReleasedEvent
} // namespace Flex