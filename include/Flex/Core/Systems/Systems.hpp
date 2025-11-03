#pragma once

namespace Flex {
	class World;

	class System {
		public:
			explicit constexpr System(World* world) :
				m_world(world) { }
			virtual ~System();

			virtual void update(double dt) = 0;
			virtual void postUpdate(double dt) = 0;

			constexpr World* getWorld() const { return m_world; }
			constexpr void setWorld(World* world) { m_world = world; }

		protected:
			[[maybe_unused]] World* m_world = nullptr;
	}; // class System
} // namespace Flex