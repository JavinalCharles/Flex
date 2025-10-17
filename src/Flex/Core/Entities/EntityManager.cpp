#include "Flex/Core/Entities/EntityManager.hpp"
#include <cassert>

using Flex::EntityID;
using Flex::EntityManager;

EntityManager::EntityManager() = default;

EntityManager::~EntityManager() = default;

EntityID EntityManager::registerEntity() {
	assert(m_livingEntities < MAX_ENTITIES && "Too much entities in existence.");

	EntityID newID;
	if (m_unusedEntityIDs.empty()) {
		newID = m_nextID++;
	}
	else {
		newID = m_unusedEntityIDs.front();
		m_unusedEntityIDs.pop();
	}
	++m_livingEntities;

	return newID;
}

void EntityManager::destroyEntity(EntityID ID) {
	if (ID > MAX_ENTITIES) return;
	m_entities.at(ID).clear();
	m_unusedEntityIDs.push(ID);
	--m_livingEntities;
}

std::size_t EntityManager::countLiveEntities() const {
	return m_livingEntities;
}