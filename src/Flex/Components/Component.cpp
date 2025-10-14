#include "Flex/Components/Component.hpp"

using namespace Flex;

Component::Component() = default;

Component::Component(Entity* owner)
	: m_owner(owner)
{

}

Component::~Component() { }

void Component::awake() { }

Entity* Component::getOwner() const {
	return m_owner;
}