#pragma once

#include <memory>
#include <optional>
#include <unordered_map>
#include <unordered_set>

#include <SFML/Graphics/Transformable.hpp>

#include "Flex/Core/Components/Component.hpp"
#include "Flex/Core/Components/ComponentPool.hpp"
#include "Flex/Core/Entities/Entity.hpp"
#include "Flex/Core/SharedContext.hpp"
#include "Flex/Events/Types/Event.hpp"
#include "Flex/Resources/ResourceManager.hpp"
#include "Flex/Scenes/SceneManager.hpp"

namespace Flex {
	using ComponentSet 			= std::unordered_set<std::type_index>;
	using EntityComponentArray 	= std::vector<ComponentSet>;
	using PoolMap 				= std::unordered_map<std::type_index, std::unique_ptr<ComponentPoolInterface>>;
	template <ComponentType CT>
	using ComponentRef		 	= std::optional<std::reference_wrapper<CT>>;
	using ResourcesManagerMap	= std::unordered_map<std::type_index, std::unique_ptr<IRM>>;

	class World {
		public:
			/// 
			/// @brief Construct a new World object
			/// @param context The context holding environment and configuration data.
			/// 
			/// @{
			World();
			explicit World(const SharedContext& context);
			/// @}

			/// @brief Destroy the World object
			virtual ~World();

			/// 
			/// @brief Spawns a new entity to the World
			/// 
			/// @return the ID of the new Entity
			///
			EntityID newEntity();

			/// 
			/// @brief Remove an Entity from the world, along with its components.
			/// 
			/// @param id The Entity to be deleted
			/// @return true If the Entity has been successfully removed.
			/// @return false If the id is not being used. (Entity already removed)
			///
			bool removeEntity(EntityID id);

			/// 
			/// @brief Construct's a CT component in-place and assigns it to Entity ID
			/// 
			/// @tparam CT The type of component
			/// @tparam Args Arguments forwarded to CT's constructor
			/// @param ID the owneer of the new Component
			/// @param args arguments forwarded to CT's constructor
			/// @return ComponentRef<CT> An std::optional containing reference to the
			/// constructed component if successful. std::nullopt otherwise.
			///
			template <ComponentType CT, typename... Args>
			ComponentRef<CT> assignComponent(EntityID ID, Args&&... args);

			/// 
			/// @brief Returns a reference to the ComponentPool of desired Component.
			/// 
			/// @tparam CT The Component type managed by the desired ComponentPool
			/// @return ComponentPool<CT>& 
			///
			template <ComponentType CT>
			ComponentPool<CT>& getPool();

			/// 
			/// @brief Geta the Component of the Entity ID
			/// 
			/// @tparam CT Component Type
			/// @param ID The Entity's ID
			/// @return ComponentRef<CT> std::optional containing reference to the 
			/// Entity's component if any, std::nullopt otherwise.
			///
			template <ComponentType CT>
			ComponentRef<CT> getComponent(EntityID ID);

			template<typename R>
			ResourceManager<R>& getManager();

			/// 
			/// @brief Handle the given event
			/// 
			/// @tparam ET The Event's type
			/// @param event the event to be handled.
			///
			template <EventType ET>
			void handleEvent(const ET& event);

			/// 
			/// @brief update the world.
			/// 
			/// @param dt time since last update
			///
			void update(double dt);

			/// 
			/// @brief A secondary update, after update()
			/// 
			/// @param dt time since last update
			///
			void postUpdate(double dt);

			/// 
			/// @brief Renders any renderable objects in the world.
			/// 
			/// @param win The window to draw with.
			///
			void draw(Window& win);
		protected:
			SceneManager				m_sceneManager;
			SharedContext				m_context;

		private:
			std::unordered_set<EntityID>	m_unusedIDs;						
			EntityComponentArray			m_ec;
			std::size_t						m_ecCount = 0u;

			PoolMap 						m_poolMap;
			ResourcesManagerMap				m_managerMap;
	}; // class World

	/////////////////////////////////////////////////////////////////////// 
	/// TEMPLATE METHOD IMPLEMENTATIONS
	///////////////////////////////////////////////////////////////////////

	template <ComponentType CT, typename... Args>
	ComponentRef<CT> World::assignComponent(EntityID id, Args&&... args) {
		if (id >= m_ec.size() || m_unusedIDs.contains(id))
			return std::nullopt;

		ComponentPool<CT>& cp = getPool<CT>();
		return cp.assign(id, std::forward<Args>(args)...);
	}

	template <ComponentType CT>
	ComponentPool<CT>& World::getPool() {
		const std::type_index TYPE_INDEX(typeid(CT));
		
		// If it does not exist, create a pool anyway.
		auto [it, inserted] = m_poolMap.try_emplace(TYPE_INDEX, std::make_unique<ComponentPool<CT>>());

		return *it->second;
	}

	template <ComponentType CT>
	ComponentRef<CT> World::getComponent(EntityID id) {
		const std::type_index TYPE_INDEX(typeid(CT));

		ComponentPool<CT>& pool = getPool<CT>();
		return pool.get(id);
	}

	template<typename R>
	ResourceManager<R>& World::getManager() {
		const std::type_index TID(typeid(R));
		auto it = m_managerMap.find(TID);

		if (it == m_managerMap.end()) {
			auto ptr = std::make_unique<ResourceManager<R>>();
			auto [newIt, _] = m_managerMap.emplace(TID, std::move(ptr));
			it = newIt;
		}

		return *static_cast<ResourceManager<R>*>(it->second.get());
	}

	template <EventType ET>
	void World::handleEvent(const ET& event) {
		m_sceneManager.handleEvent(event);
	}
} // namespace Flex