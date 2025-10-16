#pragma once

#include <memory>
#include <vector>

#include "Flex/Window/Window.hpp"

namespace Flex {

class SceneBase {
public:
    SceneBase();
    virtual ~SceneBase();

    virtual void onCreate();
    virtual void onDestroy();

    virtual void onActivate();
    virtual void onDeactivate();

    virtual void onHandleEvents(double dt) = 0;

protected:
    virtual void handleEvent(const sf::Event& event);
    virtual void update(double dt);
    virtual void postUpdate(double dt);
    virtual void draw(Window& window);

protected:
    std::vector<std::shared_ptr<SceneBase>> m_subScenes;
}; // class SceneBase

} // namespace Flex