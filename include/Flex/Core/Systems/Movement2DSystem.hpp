#pragma once

#include "Flex/Core/Systems/Systems.hpp"
#include "Flex/Core/Worlds/World.hpp"

namespace flex {
	class Movement2DSystem : public System {
		public:
			explicit constexpr Movement2DSystem(World* world) :
				System(world) { }
			virtual ~Movement2DSystem();

			virtual void update(double dt) override;
			virtual void postUpdate(double dt) override;
			
		private:
	}; // class Movement2DSystem
} // namespace flex