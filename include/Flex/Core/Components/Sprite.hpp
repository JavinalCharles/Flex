#pragma once

#include <SFML/Graphics/Sprite.hpp>

#include "Flex/Core/Components/Drawable.hpp"
#include "Flex/Core/Entities/Entity.hpp"
#include "Flex/Utilities/Utility.hpp"

namespace Flex {
	class Sprite : public Drawable, public sf::Sprite {
		public:
			Sprite(EntityID ID, const sf::Texture& texture);
			Sprite(EntityID ID, const sf::Texture& texture, const sf::IntRect& rect);
			Sprite(EntityID ID, const sf::Texture& texture, const sf::IntRect& rect, ID16_t DRAW_LAYER, ID16_t SORT_ORDER = 0u);
			Sprite(EntityID ID, const sf::Texture& texture, ID16_t DRAW_LAYER, ID16_t SORT_ORDER = 0u);
			virtual ~Sprite();

			virtual void drawOnTarget(Window& window) override;
		private:
	}; // class Sprite
} // namespace Flex