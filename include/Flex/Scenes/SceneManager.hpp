#pragma once

#include <memory>
#include <optional>
#include <queue>
#include <utility>
#include <vector>

#include <SFML/Graphics/RenderWindow.hpp>

#include "Flex/Core/SharedContext.hpp"
#include "Flex/Events/Types/Event.hpp"
#include "Flex/Scenes/SceneBase.hpp"
#include "Flex/Utilities/Utility.hpp"
#include "Flex/Window/Window.hpp"

namespace Flex {

	class SceneManager {
		public:
			using SceneData = std::pair<std::optional<ID_t>, std::weak_ptr<SceneBase>>;

			SceneManager();
			virtual ~SceneManager();

			template <SceneType ST>
			void removeScene(std::shared_ptr<SceneBase> scene);

			template <EventType ET>
			void handleEvent(const ET& event) {
				m_eventManager.post(event);
			}

			void update(double dt);
			void postUpdate(double dt);
			void draw(Window& window);

			[[nodiscard]] bool setActiveScene(ID_t sceneID);
			[[nodiscard]] std::shared_ptr<SceneBase> getActiveScene() const;
		protected:
			EventManager 			m_eventManager; 
			SharedContext 			m_sharedCcontext;
		private:
			std::vector<std::shared_ptr<SceneBase>> m_scenes;
			ID_t 				m_activeSceneID;
			std::queue<ID_t>	m_unusedSceneID;

			SharedContext*		m_context = nullptr;
	}; // class SceneManager

} // namespace Flex