#pragma once

#include <concepts>
#include <type_traits>

#include "Flex/Core/Entities/Entity.hpp"

namespace Flex {

	/// 
	/// @brief Component serves as a base class for other components.
	///
	///
	class Component {
		public:
			///
			/// @brief the ID of the Entity owning this component instance.
			///
			///
			const EntityID ownerID;

			///
			/// @brief Contstructs a Component object
			///
			///
			explicit constexpr Component(EntityID id) :
				ownerID(id) { }

			/// 
			/// @brief Destroy the Component object
			/// 
			///
			virtual ~Component();
		
	}; // class Component

	template <typename C>
	concept ComponentType = 
		std::derived_from<C, Component> && !std::is_same_v<Component, C>;

} // namespace Flex