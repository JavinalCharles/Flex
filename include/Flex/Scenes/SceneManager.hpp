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
	class World;

	class SceneManager {
		public:
			using SceneData = std::pair<std::optional<ID_t>, std::weak_ptr<SceneBase>>;
			using SceneValue = std::pair<std::optional<ID_t>, std::shared_ptr<SceneBase>>;

			SceneManager(World* containingWorld = nullptr);
			virtual ~SceneManager();
			
			template <SceneType ST, typename ...Args>
			SceneData addScene(Args... args) {
				SceneData data;
				if (m_unusedSceneID.empty()) {
					ID_t index = static_cast<ID_t>(m_scenes.size());
					try {
						m_scenes.push_back(std::make_shared<ST>(std::forward<Args>(args)...));
						data.first.emplace(index);
						data.second = m_scenes.back();
					}
					catch (const std::exception&) {
						return data; // return empty data
					}
				}
				else {
					ID_t index = m_unusedSceneID.front();
					try {
						m_scenes.at(index) = std::make_shared<ST>(std::forward<Args>(args)...);
						data.first.emplace(index);
						data.second = m_scenes.at(index);
					}
					catch (const std::exception&) {
						return data; // return empty data
					}
					m_unusedSceneID.pop();
				}
				return data;
			}

			bool removeScene(ID_t sceneID);

			template <EventType ET>
			void handleEvent(const ET& event) {
				if (!m_activeScene.first.has_value() || m_activeScene.second == nullptr)
					return;
				m_activeScene.second->handleEvent(event);
			}

			void update(double dt);
			void postUpdate(double dt);
			void draw(Window& win);

			[[nodiscard]] bool setActiveScene(ID_t sceneID);
			[[nodiscard]] std::shared_ptr<SceneBase> getActiveScene() const;
		protected:
			World*					m_containingWorld;
		private:
			std::vector<std::shared_ptr<SceneBase>> m_scenes;
			SceneValue			m_activeScene;
			bool				m_hasActiveScene = false;
			std::queue<ID_t>	m_unusedSceneID;
	}; // class SceneManager

} // namespace Flex