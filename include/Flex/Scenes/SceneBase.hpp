#pragma once

#include <concepts>
#include <memory>
#include <type_traits>
#include <vector>

#include <SFML/Graphics/RenderWindow.hpp>

#include "Flex/Events/EventManager.hpp"

namespace Flex {

	class SceneBase {
		public:
			friend class SceneManager;
			SceneBase();
			virtual ~SceneBase();

			virtual void onCreate();
			virtual void onDestroy();
			virtual void onActivate();
			virtual void onDeactivate();
			virtual void onUpdate(double dt);
			virtual void onPostUpdate(double dt);
			virtual void onDraw(sf::RenderWindow& win);

			void create();
			void destroy();
			void activate();
			void deactivate();

			void update(double dt);
			void postUpdate(double dt);
			void draw(sf::RenderWindow& win);

			template <EventType ET>
			void handleEvent(const ET& event) {
				m_eventManager.post(ET);
			}
		protected:
			EventManager							m_eventManager;
			std::vector<std::shared_ptr<SceneBase>> m_childScenes;
	}; // class SceneBase

	template <typename T>
	concept SceneType = std::derived_from<T, SceneBase> && !std::is_same_v<T, SceneBase>;
} // namespace Flex