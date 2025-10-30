#include "Flex/Core/Worlds/World.hpp"

using Flex::EntityID;
using Flex::ID_t;
using Flex::World;

World::World() = default;

World::World(const SharedContext& context) : m_context(context) { }

World::~World() = default;

EntityID World::newEntity() {
	ID_t newID;
	if (!m_unusedIDs.empty()) {
		newID = m_unusedIDs.extract(m_unusedIDs.cbegin()).value();
	}
	else {
		newID = m_ecCount;
		m_ec.emplace_back();
	}

	++m_ecCount;
	return newID;
}

bool World::removeEntity(EntityID id) {
	if (id >= m_ec.size() || m_unusedIDs.contains(id))
		return false;
	
	for (auto& ctype : m_ec.at(id)) {
		try {
			m_poolMap.at(ctype)->remove(id);
		}
		catch (const std::exception&) {
			continue;
		}
	}

	m_ec.at(id).clear();
	m_unusedIDs.insert(id);

	return true;
}

void World::update(double dt) {
	m_sceneManager.update(dt);
}
void World::postUpdate(double dt) {
	m_sceneManager.postUpdate(dt);
}
void World::draw(Window& win) {
	m_sceneManager.draw(win);
}