#pragma once

#include <array>
#include <queue>
#include <typeindex>
#include <unordered_set>

#include "Flex/Core/Components/Component.hpp"
#include "Flex/Core/Entities/Entity.hpp"
#include "Flex/Utilities/Utility.hpp"

namespace Flex {

constexpr std::size_t MAX_ENTITIES = 8000;

class EntityManager {
public:
	EntityManager();
	~EntityManager();

	EntityID registerEntity();
	template <ComponentType... componentTypes>
	EntityID registerEntity() {
		EntityID newEntity = registerEntity();

		// Bind each component type to the newly created entity
		( (void)bindComponent<componentTypes>(newEntity), ... );

		return newEntity;
	}

	template <ComponentType T>
	void bindComponent(EntityID ID) {
		m_entities.at(ID).emplace(typeid(T));
	}

	void destroyEntity(EntityID ID);
	std::size_t countLiveEntities() const;

private:
	std::queue<EntityID> m_unusedEntityIDs;
	std::array<std::unordered_set<std::type_index>,MAX_ENTITIES> m_entities{};

	std::size_t m_livingEntities = 0;
	EntityID m_nextID = 0;
}; // class	EntityManager

} // namespace Flex