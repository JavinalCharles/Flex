#pragma once

namespace Flex {

class EventManager;
class SceneManager;
class Window;

struct SharedContext {
	EventManager* eventManager = nullptr;
	SceneManager* sceneManager = nullptr;
	Window* window = nullptr;

	SharedContext();
	SharedContext(const SharedContext& other);
	SharedContext& operator=(const SharedContext& other);
}; // struct SharedContext

} // namespace Flex