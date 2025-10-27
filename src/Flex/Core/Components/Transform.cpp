#include "Flex/Core/Components/Transform.hpp"

using Flex::Component;
using Flex::EntityID;
using Flex::Transform;

Transform::Transform(EntityID id) :
	Component(id),
	sf::Transformable()
{

}

Transform::~Transform() = default;