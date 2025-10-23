#pragma once
#include <string>

#include <SFML/Window/Event.hpp>
#include "Flex/Utilities/Utility.hpp"

namespace Flex {
	struct EventBase {
		constexpr EventBase() {}
		virtual ~EventBase() = default;
	}; // struct EventBase

	template <typename Derived>
	struct Event : public EventBase {
		constexpr Event() : EventBase() { };
		~Event() = default;

		static std::string_view eventName() {
			return std::string_view(typeid(Derived).name());
		}
	}; // struct Event
} // namespace Flex