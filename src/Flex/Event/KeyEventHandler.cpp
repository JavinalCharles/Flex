#include "Flex/Event/KeyEventHandler.hpp"

using Flex::EventHandler;
using Flex::ID_t;
using Flex::KeyEventHandler;

KeyEventHandler::KeyEventHandler() 
    : EventHandler() 
{
}

KeyEventHandler::~KeyEventHandler() = default;

ID_t KeyEventHandler::registerKeyPressedCallback(KeyPressedCallback callback) {
    m_keyPressedCallbacks.push_back(std::move(callback));
    return static_cast<ID_t>(m_keyPressedCallbacks.size() - 1);
}

ID_t KeyEventHandler::registerKeyReleasedCallback(KeyReleasedCallback callback) {
    m_keyReleasedCallbacks.push_back(std::move(callback));
    return static_cast<ID_t>(m_keyReleasedCallbacks.size() - 1);
}

void KeyEventHandler::bindKeyPress(int key, ID_t callbackID) {
    if (key < 0 || key >= MAX_KEYS || callbackID >= static_cast<ID_t>(m_keyPressedCallbacks.size())) {
        return;
    }
    m_keyPressBindings[key].push_back(callbackID);
}

void KeyEventHandler::bindKeyPress(int key, KeyPressedCallback callback) {
    ID_t callbackID = registerKeyPressedCallback(std::move(callback));
    bindKeyPress(key, callbackID);
}

void KeyEventHandler::bindKeyRelease(int key, ID_t callbackID) {
    if (key < 0 || key >= MAX_KEYS || callbackID >= static_cast<ID_t>(m_keyReleasedCallbacks.size())) {
        return;
    }
    m_keyReleaseBindings[key].push_back(callbackID);
}

void KeyEventHandler::bindKeyRelease(int key, KeyReleasedCallback callback) {
    ID_t callbackID = registerKeyReleasedCallback(std::move(callback));
    bindKeyRelease(key, callbackID);
}

std::vector<std::type_index> KeyEventHandler::getEventTypes() const {
    return std::vector<std::type_index>{
        std::type_index(typeid(sf::Event::KeyPressed)),
        std::type_index(typeid(sf::Event::KeyReleased))
    };
}

void KeyEventHandler::handleEvent(const sf::Event& event) {
    event.visit(this);
}

void KeyEventHandler::operator()(const sf::Event::KeyPressed& event) {
    int key = static_cast<int>(event.code);
    if (key < 0 || key >= MAX_KEYS) {
        return;
    }
    for (ID_t callbackID : m_keyPressBindings[key]) {
        if (callbackID < static_cast<ID_t>(m_keyPressedCallbacks.size())) {
            m_keyPressedCallbacks[callbackID](event);
        }
    }
}

void KeyEventHandler::operator()(const sf::Event::KeyReleased& event) {
    int key = static_cast<int>(event.code);
    if (key < 0 || key >= MAX_KEYS) {
        return;
    }
    for (ID_t callbackID : m_keyReleaseBindings[key]) {
        if (callbackID < static_cast<ID_t>(m_keyReleasedCallbacks.size())) {
            m_keyReleasedCallbacks[callbackID](event);
        }
    }
}