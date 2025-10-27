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
		newID = m_unusedIDs.front();
		m_unusedIDs.pop();
	}
	else {
		newID = m_ecCount;
		if (newID >= BUFFER) {
			m_ec.emplace_back();
		}
	}

	++m_ecCount;
	return newID;
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