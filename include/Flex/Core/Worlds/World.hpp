#pragma once

#include "Flex/Scenes/SceneBase.hpp"
#include "Flex/Scenes/SceneManager.hpp"
#include "Flex/Utilities/Utility.hpp"

namespace Flex {
	template <std::size_t BUFFER = 5000>
	class World {
		public:

		private:
			std::array<std::vector<std::type_index>, BUFFER> 	m_entityBuffer;
			std::vector<std::vector<std::type_index>> 			m_entityVector;
			std::size_t											m_entitiesCount = 0;
	}; // class World
} // namespace Flex