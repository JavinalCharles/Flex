#pragma once

// #include <functional>
// #include <optional>
#include <limits>
#include <unordered_map>
// #include <vector>


#include "Flex/Utilities/Utility.hpp"

namespace flex {
	class IRM {
		public:
			virtual ~IRM();
	}; // class IRM

	template <typename R>
	class ResourceManager : public IRM {
		public:
			static constexpr ID_t NORESOURCE = std::numeric_limits<ID_t>::max();
			constexpr ResourceManager() = default;
			virtual ~ResourceManager() = default;

			/// 
			/// @brief Gets a reference to the resource identified by RID.
			/// 
			/// @param RID The Resource's ID
			/// @return R& Reference to the resource.
			/// @throws std::out_of_range If RID does not exist.
			/// @{
			[[nodiscard]] R& at(ID_t RID) { return m_resMap.at(RID); }
			[[nodiscard]] const R& at(ID_t RID) const { return m_resMap.at(RID); }
			/// @}


			[[nodiscard]] ID_t store(const R& RESOURCE) {
				m_resMap.insert_or_assign(m_latestID, RESOURCE);
				return m_latestID++;
			}

			[[nodiscard]] ID_t store(R&& RESOURCE) {
				m_resMap.insert_or_assign(m_latestID, std::move(RESOURCE));
				return m_latestID++;
			}

			template <typename... Args>
			[[nodiscard]] std::pair<bool, ID_t> create(Args&&... args) {
				auto [_, success] = m_resMap.try_emplace(m_latestID, std::forward<Args>(args)...);
				return std::make_pair(success, success ? m_latestID++ : NORESOURCE);
			}

		private:
			// std::vector<ID_t> m_unusedIDs; // Probably not needed.
			std::unordered_map<ID_t, R> m_resMap;
			ID_t m_latestID = 0;
	}; // class ResourceManager

	// template <typename RM>
	// concept ResourceManagerType = std::derived_from<RM, IResourceManager>;
}// namespace flex