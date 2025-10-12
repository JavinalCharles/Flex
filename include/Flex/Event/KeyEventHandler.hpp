#pragma once

#include <array>
#include <functional>
#include <optional>
#include <unordered_map>

#include <SFML/Window/Event.hpp>

namespace Flex {

constexpr int MAX_KEYS = 256;
constexpr int MOD_MASK = (1 << 4) - 1; // 0B1111
constexpr int MAX_KEYS_WITH_MOD = MAX_KEYS * (MOD_MASK + 1);

enum KEY_MOD {
    MOD_NONE  = 0,
    MOD_SHIFT = 1 << 0,
    MOD_CTRL  = 1 << 1,
    MOD_ALT   = 1 << 2,
    MOD_SUPER = 1 << 3
};

class KeyEventHandler {
public:
    using KeyCallback = std::function<void()>;
    using KeyCallbackMap = std::array<std::vector<KeyCallback>, MAX_KEYS_WITH_MOD>;

    KeyEventHandler();
    KeyEventHandler(const KeyEventHandler&) = delete;
    KeyEventHandler(KeyEventHandler&&) = delete;
    KeyEventHandler& operator=(const KeyEventHandler&) = delete;
    KeyEventHandler& operator=(KeyEventHandler&&) = delete;
    virtual ~KeyEventHandler();

    void registerKeyPress(sf::Keyboard::Key key, KeyCallback callback, std::uint16_t mods = MOD_NONE);

    void registerKeyRelease(sf::Keyboard::Key key, KeyCallback callback, std::uint16_t mods = MOD_NONE);

    void handleKeyPressed(const sf::Event::KeyPressed* e);
    void handleKeyReleased(const sf::Event::KeyReleased* e);

private:
    int computeIndex(int key, std::uint16_t mods) const;

private:
    KeyCallbackMap m_keyPressCallbacks{};
    KeyCallbackMap m_keyReleaseCallbacks{};


}; // class KeyEventHandler

} // namespace Flex