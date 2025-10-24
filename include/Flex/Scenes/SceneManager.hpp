#pragma once

#include <memory>
#include <vector>

#include "Flex/Core/SharedContext.hpp"
#include "Flex/Events/Types/Event.hpp"
#include "Flex/Events/EventManager.hpp"
#include "Flex/Scenes/SceneBase.hpp"
#include "Flex/Window/Window.hpp"

namespace Flex {

	class SceneManager {
		public:
			constexpr SceneManager() = default;


			virtual ~SceneManager();

			void addScene(std::shared_ptr<SceneBase> scene);
			void removeScene(std::shared_ptr<SceneBase> scene);

			template <EventType ET>
			void handleEvent(const ET& event) {
				m_eventManager.post(event);
			}
			void update(double dt);
			void postUpdate(double dt);
			void draw(Window& window);

			void setActiveScene(std::shared_ptr<SceneBase> scene);
			std::shared_ptr<SceneBase> getActiveScene() const;
		protected:
			EventManager 			m_eventManager; 
			SharedContext 			m_sharedCcontext;
		private:
			std::vector<std::shared_ptr<SceneBase>> m_scenes;
			std::shared_ptr<SceneBase> m_activeScene;

			
	}; // class SceneManager

} // namespace Flex