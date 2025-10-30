#include "Flex/Core/Components/Sprite.hpp"
#include "Flex/Core/Entities/Entity.hpp"

namespace Flex {
	Sprite::Sprite(EntityID ID, const sf::Texture& texture) :
		Flex::Drawable(ID), sf::Sprite(texture)
	{

	}

	Sprite::Sprite(EntityID ID, const sf::Texture& texture, const sf::IntRect& rect) :
		Flex::Drawable(ID), sf::Sprite(texture, rect)
	{

	}

	Sprite::Sprite(EntityID ID, const sf::Texture& texture, ID16_t DRAW_LAYER, ID16_t SORT_ORDER) :
		Flex::Drawable(ID, DRAW_LAYER, SORT_ORDER), sf::Sprite(texture)
	{

	}

	Sprite::Sprite(EntityID ID, const sf::Texture& texture, const sf::IntRect& rect, ID16_t DRAW_LAYER, ID16_t SORT_ORDER) :
		Flex::Drawable(ID, DRAW_LAYER, SORT_ORDER), 
		sf::Sprite(texture, rect)
	{

	}

	Sprite::~Sprite() = default;

	void Sprite::drawOnTarget(Window& window) {
		window.getRenderWindow().draw(*this);
	}
}