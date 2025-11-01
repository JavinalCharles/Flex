#pragma once

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include "Flex/Core/Components/Component.hpp"
#include "Flex/Core/Entities/Entity.hpp"
#include "Flex/Utilities/Utility.hpp"

namespace Flex {
	class Drawable : public Component {
		public:
			explicit Drawable(EntityID ID);
			Drawable(EntityID ID, ID16_t DRAW_LAYER, ID16_t SORT_ORDER = 0u);
			virtual ~Drawable();

			virtual void draw(sf::RenderTarget& targer, sf::RenderStates states) const = 0;

			constexpr ID16_t drawLayer() const { return m_layer; }
			constexpr ID16_t sortOrder() const { return m_order; }
		private:
			ID16_t m_layer = 0u;
			ID16_t m_order = 0u;
	}; // class Drawable
} // namespace Flex