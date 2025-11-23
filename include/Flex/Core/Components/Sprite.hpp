#pragma once

#include <SFML/Graphics/Sprite.hpp>

#include "Flex/Core/Components/Drawable.hpp"
#include "Flex/Core/Entities/Entity.hpp"
#include "Flex/Utilities/Utility.hpp"

namespace flex {
	class Sprite : public Drawable {
		public:
			Sprite(EntityID ID, const sf::Texture& texture);
			Sprite(EntityID ID, const sf::Texture& texture, const sf::IntRect& rect);
			Sprite(EntityID ID, const sf::Texture& texture, const sf::IntRect& rect, ID16_t DRAW_LAYER, ID16_t SORT_ORDER = 0u);
			Sprite(EntityID ID, const sf::Texture& texture, ID16_t DRAW_LAYER, ID16_t SORT_ORDER = 0u);
			virtual ~Sprite();

			virtual void draw(sf::RenderTarget& target, sf::RenderStates state) const override;
			constexpr sf::Sprite& getSprite() { return m_sprite; }
			constexpr const sf::Sprite& getSprite() const { return m_sprite; }
		private:
			sf::Sprite m_sprite;
	}; // class Sprite
} // namespace flex