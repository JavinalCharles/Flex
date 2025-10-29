#include "Flex/Core/Systems/Movement2DSystem.hpp"
#include "Flex/Core/Components/ComponentPool.hpp"
#include "Flex/Core//Components//Transform.hpp"
#include "Flex/Core/Components/Velocity2D.hpp"

using namespace Flex;

Movement2DSystem::~Movement2DSystem() = default;

void Movement2DSystem::update(double dt) {
	ComponentPool<Transform>& transformPool =  getWorld()->getPool<Transform>();
	ComponentPool<Velocity2D>& velocityPool = getWorld()->getPool<Velocity2D>();

	for (Velocity2D& vel : velocityPool.data()) {
		const EntityID ID = vel.ownerID;
		if (auto ref = transformPool.get(ID);  ref.has_value()) {
			// Transform& transform = ref.value();
			// transform.move(vel.getVelocity());
			ref.value().get().move(vel.getVelocity()); // shortcut of aboce
		}
		vel.reset();
	}
}

void Movement2DSystem::postUpdate(double dt) {

}