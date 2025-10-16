#include "Flex/Events/KeyboardEventHandler.hpp"

using Flex::EventHandler;
using Flex::ID_t;
using Flex::KeyboardEventHandler;

KeyboardEventHandler::KeyboardEventHandler() 
    : EventHandler() 
{
}

KeyboardEventHandler::~KeyboardEventHandler() = default;

ID_t KeyboardEventHandler::registerKeyPressedCallback(KeyPressedCallback callback) {
    m_keyPressedCallbacks.push_back(std::move(callback));
    return static_cast<ID_t>(m_keyPressedCallbacks.size() - 1);
}

ID_t KeyboardEventHandler::registerKeyReleasedCallback(KeyReleasedCallback callback) {
    m_keyReleasedCallbacks.push_back(std::move(callback));
    return static_cast<ID_t>(m_keyReleasedCallbacks.size() - 1);
}

void KeyboardEventHandler::bindKeyPress(ID_t key, ID_t callbackID) {
    if (key < 0 || key >= MAX_KEYS || callbackID >= static_cast<ID_t>(m_keyPressedCallbacks.size())) {
        return;
    }
    m_keyPressBindings[key].push_back(callbackID);
}

void KeyboardEventHandler::bindKeyPress(ID_t key, KeyPressedCallback callback) {
    ID_t callbackID = registerKeyPressedCallback(std::move(callback));
    bindKeyPress(key, callbackID);
}

void KeyboardEventHandler::bindKeyRelease(ID_t key, ID_t callbackID) {
    if (key < 0 || key >= MAX_KEYS || callbackID >= static_cast<ID_t>(m_keyReleasedCallbacks.size())) {
        return;
    }
    m_keyReleaseBindings[key].push_back(callbackID);
}

void KeyboardEventHandler::bindKeyRelease(ID_t key, KeyReleasedCallback callback) {
    ID_t callbackID = registerKeyReleasedCallback(std::move(callback));
    bindKeyRelease(key, callbackID);
}

std::vector<std::type_index> KeyboardEventHandler::getEventTypes() const {
    return std::vector<std::type_index>{
        std::type_index(typeid(sf::Event::KeyPressed)),
        std::type_index(typeid(sf::Event::KeyReleased))
    };
}

bool KeyboardEventHandler::handleEvent(const sf::Event::KeyPressed& event) {
	ID_t key = static_cast<ID_t>(event.code);
	if (key >= MAX_KEYS) return false;

	for (ID_t callbackID : m_keyPressBindings.at(key)) {
		if (callbackID >= static_cast<ID_t>(m_keyPressedCallbacks.size()))
			continue;
		m_keyPressedCallbacks.at(callbackID)(event);
	}
	return true;
}

bool KeyboardEventHandler::handleEvent(const sf::Event::KeyReleased& event) {
	ID_t key = static_cast<int>(event.code);
	if (key >= MAX_KEYS) return false;
	for (ID_t callbackID : m_keyReleaseBindings[key]) {
		if (callbackID >= static_cast<ID_t>(m_keyReleasedCallbacks.size())) 
			continue;
		m_keyReleasedCallbacks[callbackID](event);
	}
	return true;
}