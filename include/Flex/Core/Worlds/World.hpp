#pragma once

#include <optional>
#include <stdexcept>
#include <unordered_map>
#include <unordered_set>

#include <SFML/Graphics/Transformable.hpp>

#include "Flex/Core/Components/Component.hpp"
#include "Flex/Core/Components/ComponentPool.hpp"
#include "Flex/Core/Entities/Entity.hpp"
#include "Flex/Core/SharedContext.hpp"
#include "Flex/Scenes/SceneManager.hpp"

namespace Flex {
	using ComponentSet 			= std::unordered_set<std::type_index>;
	using EntityComponentArray 	= std::vector<ComponentSet>;
	using ComponentMap 			= std::unordered_map<std::type_index, std::unique_ptr<ComponentPoolInterface>>;
	template <ComponentType CT>
	using ComponentRef		 	= std::optional<std::reference_wrapper<CT>>;

	class World {
		public:
			World();
			explicit World(const SharedContext& context);
			virtual ~World();

			EntityID newEntity();

			bool removeEntity(EntityID id);
			
			template <ComponentType CT, typename... Args>
			ComponentRef<CT> assignComponent(EntityID id, Args&&... args) {
				if (id >= m_ec.size() || m_unusedIDs.contains(id))
					return std::nullopt;

				std::type_index tindex(typeid(CT));

				// If the component map does not have the necessary component pool
				// then attempt to create one. Otherwise, find it and use its iterator it.
				auto [it, inserted] = m_componentMap.try_emplace(tindex, std::make_unique<ComponentPool<CT>>());
				
				// Down cast to it's proper form. Since std::type_index and ComponentType
				// context is being used here, The pool should be able to safely casted via
				// static_cast.
				ComponentPool<CT>& cp = static_cast<ComponentPool<CT>&>(*it->second);

				// Finally, create the component in the pool.
				CT& data = cp.emplace(id, std::forward<Args>(args)...);

				return std::make_optional(std::ref(data));
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

				auto it = m_componentMap.find(tindex);
				if (it == m_componentMap.end())
					throw std::out_of_range("World does not have the specified component pool.");

				return it->second.get();
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
			EntityComponentArray			m_ec;
			std::size_t						m_ecCount = 0;

			ComponentMap 					m_componentMap;
	}; // class World
} // namespace Flex