#pragma once

#include <array>
#include <memory>
#include <stdexcept>
#include <unordered_map>
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

	#ifdef WORLD_ARRAY_BUFFER
		#if WORLD_ARRAY_BUFFER > 0
			constexpr std::size_t BUFFER = min(WORLD_ARRAY_BUFFER, 8192);
		#else
			constexpr std::size_t BUFFER = 2048;
		#endif
	#else
		constexpr std::size_t BUFFER = 2048;
	#endif

	class World {
		public:
			using ComponentList 		= std::unordered_set<std::type_index>;
			using EntityComponentBuffer = std::array<ComponentList, BUFFER>;
			using EntityComponentArray 	= std::vector<ComponentList>;
			using ComponentMap 			= std::unordered_map<std::type_index, std::unique_ptr<ComponentPoolInterface>>;
		
			World();
			explicit World(const SharedContext& context);
			virtual ~World();

			EntityID newEntity();

			bool removeEntity(EntityID id);
			
			template <ComponentType CT, typename... Args>
			CT& assignComponent(EntityID id, Args&&... args) {
				if (id >= BUFFER + m_ec.size() || m_unusedIDs.contains(id))
					throw std::out_of_range("Entity no longer exist!");
				std::type_index tindex(typeid(CT));

				auto [it, inserted] = m_componentMap.try_emplace(tindex, std::make_unique<ComponentPool<CT>>());

				ComponentPool<CT>& cp = static_cast<ComponentPool<CT>&>(*it->second);
				CT& data = cp.emplace(id, std::forward<Args>(args)...);

				if (id < BUFFER) m_ecBuffer.at(id).insert(tindex);
				else m_ec.at(id - BUFFER).insert(tindex);

				return data;
			}

			template <ComponentType CT>
			ComponentPool<CT>& getPool() {
				std::type_index tindex(typeid(CT));
				
				// If it does not exist, create one anyway.
				auto [it, inserted] = m_componentMap.try_emplace(tindex, std::make_unique<ComponentPool<CT>>());

				return *it->second;
			}

			template <ComponentType CT>
			CT& getComponent(EntityID id) {
				std::type_index tindex(typeid(CT));

				auto it = m_componentMap.find(id);
				if (it == m_componentMap.end())
					throw std::out_of_range("World does not have the specified component pool.");

				return it->second.get(id);
			}

			template <EventType ET>
			void handleEvent(const ET& event) {
				m_sceneManager.handleEvent(event);
			}

			void update(double dt);
			void postUpdate(double dt);
			void draw(Window& win);
		protected:
			SceneManager				m_sceneManager;
			SharedContext				m_context;

		private:
			std::unordered_set<EntityID>	m_unusedIDs;							
			EntityComponentBuffer	 		m_ecBuffer{};
			EntityComponentArray			m_ec;
			std::size_t						m_ecCount = 0;

			ComponentMap 					m_componentMap;
	}; // class World
} // namespace Flex