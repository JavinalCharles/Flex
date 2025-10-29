#pragma once

#include <limits>
#include <SFML/System/Vector2.hpp>

#include "Flex/Core/Components/Component.hpp"
#include "Flex/Core/Entities/Entity.hpp"

namespace Flex {
	class Velocity2D : public Component {
		public:
			explicit constexpr Velocity2D(EntityID id) :
				Component(id) { }
			constexpr Velocity2D(EntityID id, float maxSpeed) :
				Component(id), m_maxSpeed(maxSpeed) { }
			virtual ~Velocity2D();

			void setMove(const sf::Vector2f& vel);
			void setMaximumSpeed(float speed);
			constexpr const sf::Vector2f& getVelocity() const {
				return m_velocity;
			}
		private:
			void clampVelocity();
		private:
			float 			m_maxSpeed = std::numeric_limits<float>::max() / 2.f;
			sf::Vector2f 	m_velocity{};
	}; // class Velocity
} // namespace Flex