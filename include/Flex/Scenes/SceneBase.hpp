#pragma once

#include <memory>
#include <vector>

#include "Flex/Window/Window.hpp"

namespace Flex {

class SceneBase {
public:
    SceneBase();
    virtual ~SceneBase();

    void create();
    void destroy();

    void activate();
    void deactivate();

	virtual void onCreate() = 0;
	virtual void onDestroy() = 0;
	virtual void onActiviate() = 0;
	virtual void onDeactivate() = 0;

protected:
    virtual void handleEvent(const sf::Event& event);
    virtual void update(double dt);
    virtual void postUpdate(double dt);
    virtual void draw(Window& window);
protected:
    std::vector<std::shared_ptr<SceneBase>> m_subScenes;
}; // class SceneBase

} // namespace Flex