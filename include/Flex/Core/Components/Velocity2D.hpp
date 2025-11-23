#pragma once

#include <limits>
#include <SFML/System/Vector2.hpp>

#include "Flex/Core/Components/Component.hpp"
#include "Flex/Core/Entities/Entity.hpp"

namespace flex {
	/// 
	/// @brief Velocity2D represent an Entity's velocity in a 2D plane.
	/// 
	///
	class Velocity2D : public Component {
		public:
			/// 
			/// @brief Creates a Velocity2D object
			/// @param id ID of the owning Entity
			/// @param maxSpeed  sets the maximum length the Velocity's vector
			/// 
			/// @{
			explicit constexpr Velocity2D(EntityID id) :
				Component(id) { }
			constexpr Velocity2D(EntityID id, float maxSpeed) :
				Component(id), m_maxSpeed(maxSpeed) { }
			/// @}

			/// 
			/// @brief Destroy the Velocity 2 D object
			/// 
			///
			virtual ~Velocity2D();

			/// 
			/// @brief sets the current velocity of the owning Entity
			/// 
			/// @param vel The current velocity
			///
			void set(const sf::Vector2f& vel);

			/// 
			/// @brief Set the maximum speed of the owning Entity.
			/// 
			/// @param maxSpeed maximum speed
			///
			void setMaximumSpeed(float maxSpeed);

			/// 
			/// @brief Get the Velocity
			/// 
			/// @return constexpr const sf::Vector2f& 
			///
			constexpr const sf::Vector2f& get() const {
				return m_velocity;
			}

			/// 
			/// @brief resets the velocity to {0, 0}
			/// 
			///
			void reset();
		private:

			/// @brief Called after each Velocity2D::set() call.
			void clampVelocity();
		private:
			/// @brief The maximum speed of the owning entity.
			float 			m_maxSpeed = std::numeric_limits<float>::max() / 2.f;

			/// @brief Current velocity of the entity.
			sf::Vector2f 	m_velocity{};
	}; // class Velocity
} // namespace flex