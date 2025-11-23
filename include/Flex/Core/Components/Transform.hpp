#pragma once

#include <SFML/Graphics/Transformable.hpp>

#include "Flex/Core/Components/Component.hpp"

namespace flex {
	class Transform : public Component, public sf::Transformable {
		public:
			Transform(EntityID ownerID);
			virtual ~Transform();
	}; // class Transform
} // namespace flex