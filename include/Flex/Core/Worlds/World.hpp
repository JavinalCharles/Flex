#pragma once

#include <array>
#include <unordered_set>
#include <vector>

#include <SFML/Graphics/Transformable.hpp>

#include "Flex/Core/Components/Component.hpp"
#include "Flex/Core/Components/ComponentPool.hpp"
#include "Flex/Core/SharedContext.hpp"
#include "Flex/Events/EventManager.hpp"
#include "Flex/Scenes/SceneBase.hpp"
#include "Flex/Scenes/SceneManager.hpp"
#include "Flex/Utilities/Utility.hpp"

namespace Flex {
	template <std::size_t BUFFER = 2048>
	class World {
		public:
			using ComponentList 			= std::unordered_set<std::type_index>;
			using EntityComponentBuffer 	= std::array<ComponentList, BUFFER>;
			using EntityComponentArray 		= std::vector<ComponentList>;
			using TransformBuffer			= std::array<std::unique_ptr<sf::Transformable>, BUFFER>;
			using TransformArray 			= std::vector<std::unique_ptr<sf::Transformable>>;
		
			World() = default;
			World(const SharedContext& context) :
				m_context(context) { }
			virtual ~World() = default;

			template <EventType ET>
			void handleEvent(const ET& event) {
				m_sceneManager.handleEvent(event);
			}

			void update(double dt) {
				m_sceneManager.update(dt);
			}
			void postUpdate(double dt) {
				m_sceneManager.postUpdate(dt);
			}
			void draw(Window& win) {
				m_sceneManager.draw(win);
			}

		protexted:
			SceneManager				m_sceneManager;
			SharedContext				m_context;

		private:
			std::queue<EntityID>		m_unusedIDs;							
			EntityComponentBuffer	 	m_ecBuffer{};
			EntityComponentArray		m_ec;
			std::size_t					m_ecCount = 0;

			TransformBuffer				m_tBuffer{};
			TransformArray				m_tArray;
	}; // class World
} // namespace Flex