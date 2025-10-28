#pragma once

#include <functional>
#include <optional>
#include <unordered_map>
#include <utility>
#include <vector>

#include "Flex/Core/Components/Component.hpp"
#include "Flex/Core/Entities/Entity.hpp"

namespace Flex {
	class ComponentPoolInterface {
		public:
			virtual ~ComponentPoolInterface();
			virtual void remove(EntityID id) = 0;
	}; // class ComponentPoolInterface

	template <ComponentType CT>
	class ComponentPool : public ComponentPoolInterface {
		public:
			using ComponentRef = std::optional<std::reference_wrapper<CT>>;
			ComponentPool() : ComponentPoolInterface() {}
			virtual ~ComponentPool() = default;

			template <typename ...Args>
			CT& emplace(EntityID id, Args&&... args) {
				auto it = m_entityToIndex.find(id);
				if (it != m_entityToIndex.end()) {
					return m_data.at(it->second);
				}
				std::size_t index = m_data.size();
				m_data.emplace_back(std::forward<Args>(args)...);
				m_entityToIndex[id] = index;
				m_indexToEntity.push_back(id);

				return m_data.back();
			}

			void remove(EntityID id) override {
				auto it = m_entityToIndex.find(id);
				if (it == m_entityToIndex.end()) return;

				std::size_t index = it->second;
				std::size_t lastIndex = m_data.size() - 1;

				if (index != lastIndex) {
					m_data[index] = std::move(m_data[lastIndex]);
					EntityID movedEntity = m_indexToEntity[lastIndex];
					m_indexToEntity[index] = movedEntity;
					m_entityToIndex[movedEntity] = index;
				}

				m_data.pop_back();
				m_indexToEntity.pop_back();
				m_entityToIndex.erase(it);
			}

			ComponentRef get(EntityID id) {
				auto it = m_entityToIndex.find(id);
				if (it == m_entityToIndex.end())
					return std::nullopt;
				return std::make_optional(std::ref(m_data.at(it->second)));
			}
		private:
			std::vector<CT>								m_data;
			std::unordered_map<EntityID, std::size_t> 	m_entityToIndex;
			std::vector<EntityID>						m_indexToEntity;
	}; // class ComponentPool

} // namespace Flex