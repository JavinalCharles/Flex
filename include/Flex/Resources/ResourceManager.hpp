#pragma once

#include <functional>
#include <optional>
#include <unordered_map>

#include "Flex/Utilities/Utility.hpp"

namespace Flex {

	template <typename R>
	class ResourceManager {
		public:
			constexpr ResourceManager() = default;
			virtual ~ResourceManager() = default;

			/// 
			/// @brief Gets a reference to the desired resource
			/// 
			/// @param RID The Resource's ID
			/// @return R& Reference to the resource.
			std::optional<std::reference_wrapper<R>> get(ID_t RID) const noexcept {
				try {
					return std::make_optional(std::ref(m_resMap.at(RID)));
				}
				catch (const std::exception&){
					return std::nullopt;
				}
			}

			[[nodiscard]] ID_t store(const R& RESOURCE) {
				m_resMap.insert_or_assign(m_latestID, RESOURCE);
				return m_latestID++;
			}

			[[nodiscard]] ID_t store(R&& RESOURCE) {
				m_resMap.insert_or_assign(m_latestID, std::move(RESOURCE));
				return m_latestID++;
			}

		private:
			std::unordered_map<ID_t, R> m_resMap;
			ID_t m_latestID = 0;
	}; // class ResourceManager
}// namespace Flex