#pragma once

#include <memory>
#include <vector>

#include "Flex/Core/SharedContext.hpp"
#include "Flex/Scenes/SceneBase.hpp"
#include "Flex/Window/Window.hpp"

namespace Flex {

class SceneManager {
public:
    SceneManager();
    ~SceneManager();

    void addScene(std::shared_ptr<SceneBase> scene);
    void removeScene(std::shared_ptr<SceneBase> scene);

    void handleEvents(const sf::Event& event);
    void update(double dt);
    void postUpdate(double dt);
    void draw(Window& window);

    void setActiveScene(std::shared_ptr<SceneBase> scene);
    std::shared_ptr<SceneBase> getActiveScene() const;
private:
    std::vector<std::shared_ptr<SceneBase>> m_scenes;
    std::shared_ptr<SceneBase> m_activeScene;
    
    SharedContext m_sharedCcontext;
}; // class SceneManager

} // namespace Flex