#pragma once

#include <concepts>
#include <functional>
#include <typeindex>
#include <type_traits>
#include <unordered_map>
#include <vector>

#include "Flex/Events/Types/Event.hpp"

namespace Flex {
	class EventManager {
		public:
			EventManager();
			EventManager(const EventManager&) = delete;
			EventManager(EventManager&&) = delete;
			EventManager& operator=(const EventManager&) = delete;
			EventManager& operator=(EventManager&&) = delete;
			virtual ~EventManager();

			template <EventType ET>
			void subscribe(std::function<void(const ET&)> handler) {
				std::type_index eventID(typeid(ET));
				auto wrapper = [handler = std::move(handler)](const EventBase& e) {
					handler(static_cast<const ET&>(e));
				}
				m_subscribers[eventID].push_back(std::move(wrapper));
			}

			template <EventType ET>
			void post() {
				std::type_index eventID(typeid(ET));
				auto it = m_subscribers.find(eventID);
				if (it == m_subscribers.end()) return;

				ET event;
				for (auto& fn : it->second)
					fn(event);
			}

			template <EventType ET>
			void post(const ET& event) {
				std::type_index eventID(typeid(ET));
				auto it = m_subscribers.find(eventID);
				if (it == m_subscribers.end()) return;

				for (auto& fn : it->second)
					fn(event);
			}

			template <EventType ET, typename ...Args>
			void post(Args&&... args) {
				std::type_index eventID(typeid(ET));
				auto it = m_subscribers.find(eventID);
				if (it == m_subscribers.end()) return;

				ET event(std::forward<Args>(args)...);

				for (auto& fn : it->second)
					fn(event);
			}

		private:
			std::unordered_map<std::type_index, std::vector<std::function<void(const EventBase&)>>> m_subscribers;

	}; // class EventManager
} // namespace Flex