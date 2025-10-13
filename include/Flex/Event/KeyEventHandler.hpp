#pragma once

#include <array>
#include <functional>
#include <vector>
#include <SFML/Window/Event.hpp>

#include "Flex/Event/EventHandler.hpp"
#include "Flex/Utility/Utility.hpp"


namespace Flex {

class KeyEventHandler : public EventHandler {
public:
    using KeyPressedCallback = std::function<void(const sf::Event::KeyPressed&)>;
    using KeyReleasedCallback = std::function<void(const sf::Event::KeyReleased&)>;
    static constexpr int MAX_KEYS = 256;

    KeyEventHandler();
    KeyEventHandler(const KeyEventHandler&) = delete;
    KeyEventHandler(KeyEventHandler&&) = delete;
    KeyEventHandler& operator=(const KeyEventHandler&) = delete;
    KeyEventHandler& operator=(KeyEventHandler&&) = delete;
    virtual ~KeyEventHandler();

    ID_t registerKeyPressedCallback(KeyPressedCallback callback);
    ID_t registerKeyReleasedCallback(KeyReleasedCallback callback);

    void bindKeyPress(int key, ID_t callbackID);
    void bindKeyPress(int key, KeyPressedCallback callback);

    void bindKeyRelease(int key, ID_t callbackID);
    void bindKeyRelease(int key, KeyReleasedCallback callback);

    virtual std::vector<std::type_index> getEventTypes() const override;
    virtual void handleEvent(const sf::Event& event) override;

    void operator()(const sf::Event::KeyPressed& event);
    void operator()(const sf::Event::KeyReleased& event);
private:
    std::array<std::vector<ID_t>, MAX_KEYS> m_keyPressBindings{};
    std::array<std::vector<ID_t>, MAX_KEYS> m_keyReleaseBindings{};

    std::vector<KeyPressedCallback> m_keyPressedCallbacks{};
    std::vector<KeyReleasedCallback> m_keyReleasedCallbacks{};
}; // class KeyPressEventHandler
} // namespace Flex