#include "Flex/Events/MouseEventHandler.hpp"

using Flex::EventHandler;
using Flex::ID_t;
using Flex::MouseEventHandler;

MouseEventHandler::MouseEventHandler() 
	: EventHandler() 
{
}

MouseEventHandler::~MouseEventHandler() = default;

ID_t MouseEventHandler::registerMouseButtonPressedCallback(MouseButtonPressedCallback callback) {
	m_mouseButtonPressedCallbacks.push_back(std::move(callback));
	return static_cast<ID_t>(m_mouseButtonPressedCallbacks.size() - 1);
}

ID_t MouseEventHandler::registerMouseButtonReleasedCallback(MouseButtonReleasedCallback callback) {
	m_mouseButtonReleasedCallbacks.push_back(std::move(callback));
	return static_cast<ID_t>(m_mouseButtonReleasedCallbacks.size() - 1);
}

void MouseEventHandler::bindMouseButtonPress(ID_t button, ID_t callbackID) {
	if (button < 0 || button >= MAX_BUTTONS || callbackID >= static_cast<ID_t>(m_mouseButtonPressedCallbacks.size())) {
		return;
	}
	m_mouseButtonPressBindings[button].push_back(callbackID);
}

void MouseEventHandler::bindMouseButtonPress(ID_t button, MouseButtonPressedCallback callback) {
	ID_t callbackID = registerMouseButtonPressedCallback(std::move(callback));
	bindMouseButtonPress(button, callbackID);
}

void MouseEventHandler::bindMouseButtonRelease(ID_t button, ID_t callbackID) {
	if (button < 0 || button >= MAX_BUTTONS || callbackID >= static_cast<ID_t>(m_mouseButtonReleasedCallbacks.size())) {
		return;
	}
	m_mouseButtonReleaseBindings[button].push_back(callbackID);
}

void MouseEventHandler::bindMouseButtonRelease(ID_t button, MouseButtonReleasedCallback callback) {
	ID_t callbackID = registerMouseButtonReleasedCallback(std::move(callback));
	bindMouseButtonRelease(button, callbackID);
}

std::vector<std::type_index> MouseEventHandler::getEventTypes() const {
	return std::vector<std::type_index>{
		std::type_index(typeid(sf::Event::MouseButtonPressed)),
		std::type_index(typeid(sf::Event::MouseButtonReleased)),
		std::type_index(typeid(sf::Event::MouseMoved)),
		std::type_index(typeid(sf::Event::MouseWheelScrolled)),
		std::type_index(typeid(sf::Event::MouseEntered)),
		std::type_index(typeid(sf::Event::MouseLeft)),
		std::type_index(typeid(sf::Event::MouseMovedRaw))
	};
}

bool MouseEventHandler::handleEvent(const sf::Event::MouseButtonPressed& event) {
	ID_t button = static_cast<int>(event.button);
	if (button >= MAX_BUTTONS) return false;

	// Invoke all callbacks bound to this button press
	for (ID_t callbackID : m_mouseButtonPressBindings[button]) {
		if (callbackID >= m_mouseButtonPressedCallbacks.size())
			return;
		m_mouseButtonPressedCallbacks[callbackID](event);
	}
	return true;
}
bool MouseEventHandler::handleEvent(const sf::Event::MouseButtonReleased& event) {
	int button = static_cast<int>(event.button);
	if (button >= MAX_BUTTONS) return false;

	// Invoke all callbacks bound to this button release
	for (ID_t callbackID : m_mouseButtonReleaseBindings[button]) {
		if (callbackID < m_mouseButtonReleasedCallbacks.size())
			return;
		m_mouseButtonReleasedCallbacks[callbackID](event);
	}
	return true;
}