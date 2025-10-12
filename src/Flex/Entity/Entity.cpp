#include <Flex/Entity/Entity.hpp>

using Flex::Entity;

std::size_t Entity::s_count = 0; // Static Member Initialization

Entity::Entity() :
	sf::Transformable(), 
	ID(++s_count)
{

};

Entity::Entity(Flex::SharedContext* context) :
	sf::Transformable(),
	ID(++s_count),
	m_context(context)
{

}

Entity::~Entity() { }


void Entity::awake() {
	for (auto [_, component] : m_components) {
		if (component != nullptr)
			component->awake();
	}
}

void Entity::setStatic(bool isStatic) {
	m_static = isStatic;
}

void Entity::queueForRemoval(bool remove) {
	m_readyForRemoval = remove;
}