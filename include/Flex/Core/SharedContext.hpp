#pragma once

namespace flex {

class EventManager;
class SceneManager;
class Window;

struct SharedContext {
	EventManager* eventManager = nullptr;
	SceneManager* sceneManager = nullptr;
	Window* window = nullptr;

	constexpr SharedContext() = default;
	constexpr SharedContext(const SharedContext& other) :
		eventManager(other.eventManager),
		sceneManager(other.sceneManager),
		window(other.window)
	{

	}
	SharedContext& operator=(const SharedContext& other);
}; // struct SharedContext

} // namespace flex