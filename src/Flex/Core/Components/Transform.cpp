#include "Flex/Core/Components/Transform.hpp"

using flex::Component;
using flex::EntityID;
using flex::Transform;

Transform::Transform(EntityID id) :
	Component(id),
	sf::Transformable()
{

}

Transform::~Transform() = default;