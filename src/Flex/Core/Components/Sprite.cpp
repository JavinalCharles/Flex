#include "Flex/Core/Components/Sprite.hpp"
#include "Flex/Core/Entities/Entity.hpp"

namespace flex {
	Sprite::Sprite(EntityID ID, const sf::Texture& texture) :
		Flex::Drawable(ID), m_sprite(texture)
	{

	}

	Sprite::Sprite(EntityID ID, const sf::Texture& texture, const sf::IntRect& rect) :
		Flex::Drawable(ID), m_sprite(texture, rect)
	{

	}

	Sprite::Sprite(EntityID ID, const sf::Texture& texture, ID16_t DRAW_LAYER, ID16_t SORT_ORDER) :
		Flex::Drawable(ID, DRAW_LAYER, SORT_ORDER), m_sprite(texture)
	{

	}

	Sprite::Sprite(EntityID ID, const sf::Texture& texture, const sf::IntRect& rect, ID16_t DRAW_LAYER, ID16_t SORT_ORDER) :
		Flex::Drawable(ID, DRAW_LAYER, SORT_ORDER), 
		m_sprite(texture, rect)
	{

	}

	Sprite::~Sprite() = default;

	void Sprite::draw(sf::RenderTarget& target, sf::RenderStates state) const {
		target.draw(m_sprite, state);
	}
}