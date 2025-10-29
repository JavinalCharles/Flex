#pragma once

#include <concepts>

#include "Flex/Core/Entities/Entity.hpp"

namespace Flex {

	class Component {
		public:
			const EntityID ownerID;
			explicit constexpr Component(EntityID id) :
				ownerID(id)
			{

			}

			virtual ~Component();
		
	}; // class Component

	template <typename C>
	concept ComponentType = std::derived_from<C, Component>;

} // namespace Flex