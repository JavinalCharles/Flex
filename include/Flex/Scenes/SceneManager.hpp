#pragma once

#include <limits>
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
			
			template <SceneType ST, typename ...Args>
			SceneData addScene(Args... args) {
				SceneData data;
				if (m_unusedSceneID.empty()) {
					ID_t index = m_scenes.size();
					try {
						m_scenes.push_back(std::make_shared<ET>(std::forward<Args>(args)...));
					}
					catch (const std::exception&) {
						return data;
					}
					data.first.emplace(index);
					data.second = m_scenes.back();
				}
				else {
					ID_t index = m_unusedSceneID.front();
					try {
						m_scenes.at(index) = std::make_shared<ET>(std::forward<Args>(args)...);
					}
					catch (const std::exception&) {
						return data;
					}
					data.first.emplace(index);
					data.second = m_scenes.at(index);
					m_unusedSceneID.pop();
				}
				return data;
			}

			bool removeScene(ID_t sceneID);

			template <EventType ET>
			void handleEvent(const ET& event) {
				m_eventManager.post(event);
			}

			void update(double dt);
			void postUpdate(double dt);
			void draw(Window& win);

			[[nodiscard]] bool setActiveScene(ID_t sceneID);
			[[nodiscard]] std::shared_ptr<SceneBase> getActiveScene() const;
		protected:
			EventManager 			m_eventManager; 
			SharedContext 			m_sharedCcontext;
		private:
			std::vector<std::shared_ptr<SceneBase>> m_scenes;
			ID_t 				m_activeSceneID = std::numeric_limits<ID_t>::max();
			bool				m_hasActiveScene = false;
			std::queue<ID_t>	m_unusedSceneID;
	}; // class SceneManager

} // namespace Flex