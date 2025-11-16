#include "Flex/Core/Systems/Movement2DSystem.hpp"
#include "Flex/Core/Components/ComponentPool.hpp"
#include "Flex/Core//Components//Transform.hpp"
#include "Flex/Core/Components/Velocity2D.hpp"

using namespace Flex;

Movement2DSystem::~Movement2DSystem() = default;

void Movement2DSystem::update(double dt) {
	if (m_world == nullptr)
		return;
	ComponentPool<Transform>& transformPool =  m_world->getPool<Transform>();
	ComponentPool<Velocity2D>& velocityPool = m_world->getPool<Velocity2D>();

	if (transformPool.empty() || velocityPool.empty())
		return;

	for (Velocity2D& vel : velocityPool.data()) {
		const EntityID ID = vel.ownerID;
		if (auto ref = transformPool.get(ID);  ref.has_value()) {
			ref.value().get().move(vel.get());
		}
		vel.reset();
	}
}

void Movement2DSystem::postUpdate(double dt) {

}