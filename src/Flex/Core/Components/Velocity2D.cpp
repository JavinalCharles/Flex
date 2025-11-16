#include "Flex/Core/Components/Velocity2D.hpp"
#include "SFML/System/Vector2.hpp"

using Flex::Velocity2D;

Velocity2D::~Velocity2D() { }

void Velocity2D::set(const sf::Vector2f& vel) {
	m_velocity = vel;

	clampVelocity();
}

void Velocity2D::setMaximumSpeed(float ms) {
	m_maxSpeed = +ms;
}

void Velocity2D::clampVelocity() {
	if (m_velocity.lengthSquared() > (m_maxSpeed * m_maxSpeed)) {
		m_velocity *= m_maxSpeed / m_velocity.length();
	}
}

void Velocity2D::reset() {
	m_velocity.x = 0;
	m_velocity.y = 0;
}