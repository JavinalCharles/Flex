#include <Flex/Event/KeyEventHandler.hpp>

using Flex::KeyEventHandler;

KeyEventHandler::KeyEventHandler() = default;
KeyEventHandler::~KeyEventHandler() = default;

int KeyEventHandler::computeIndex(int key, std::uint16_t mods) const {
    if (key < 0 || key >= MAX_KEYS || (mods & ~MOD_MASK)) return -1; // Invalid modifier bits
    return (static_cast<int>(mods) << 8) | key;
}

void KeyEventHandler::registerKeyPress(sf::Keyboard::Key key, KeyCallback callback, std::uint16_t mods) {
    int index = computeIndex(static_cast<int>(key), mods);
    if (index != -1) {
        m_keyPressCallbacks[index].push_back(std::move(callback));
    }
}

void KeyEventHandler::registerKeyRelease(sf::Keyboard::Key key, KeyCallback callback, std::uint16_t mods) {
    int index = computeIndex(static_cast<int>(key), mods);
    if (index != -1) {
        m_keyReleaseCallbacks[index].push_back(std::move(callback));
    }
}

void KeyEventHandler::handleKeyPressed(const sf::Event::KeyPressed* e) {
    if (!e) return;
    std::uint16_t mods = MOD_NONE;
    if (e->shift) mods |= MOD_SHIFT;
    if (e->control) mods |= MOD_CTRL;
    if (e->alt) mods |= MOD_ALT;
    if (e->system) mods |= MOD_SUPER;

    int index = computeIndex(static_cast<int>(e->code), mods);
    if (index != -1) {
        for (const auto& callback : m_keyPressCallbacks[index]) {
            if (callback) callback();
        }
    }
}

void KeyEventHandler::handleKeyReleased(const sf::Event::KeyReleased* e) {
    if (!e) return;
    std::uint16_t mods = MOD_NONE;
    if (e->shift) mods |= MOD_SHIFT;
    if (e->control) mods |= MOD_CTRL;
    if (e->alt) mods |= MOD_ALT;
    if (e->system) mods |= MOD_SUPER;

    int index = computeIndex(static_cast<int>(e->code), mods);
    if (index != -1) {
        for (const auto& callback : m_keyReleaseCallbacks[index]) {
            if (callback) callback();
        }
    }
}