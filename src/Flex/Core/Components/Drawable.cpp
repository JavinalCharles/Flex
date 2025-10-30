#include "Flex/Core/Components/Drawable.hpp"

using namespace Flex;

Drawable::Drawable(EntityID ID) : Component(ID) { }

Drawable::Drawable(EntityID ID, ID16_t LAYER, ID16_t ORDER) :
	Component(ID), m_layer(LAYER), m_order(ORDER) { }

Drawable::~Drawable() = default;