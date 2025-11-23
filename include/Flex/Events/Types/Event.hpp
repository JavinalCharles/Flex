#pragma once

#include <SFML/Window/Event.hpp>

namespace flex {
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

	template <typename T>
	concept EventType = std::derived_from<T, EventBase> && !std::is_same_v<T, EventBase>;
} // namespace flex