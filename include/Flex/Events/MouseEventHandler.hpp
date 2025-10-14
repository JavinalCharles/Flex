#pragma once

#include <array>
#include <functional>
#include <unordered_map>
#include <vector>

#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Mouse.hpp>

#include "Flex/Events/EventHandler.hpp"

namespace Flex {

class MouseEventHandler : public EventHandler {
public:
    using MouseButtonPressedCallback = std::function<void(const sf::Event::MouseButtonPressed&)>;
    using MouseButtonReleasedCallback = std::function<void(const sf::Event::MouseButtonReleased&)>;
    static constexpr ID_t MAX_BUTTONS = sf::Mouse::ButtonCount;

public:
    MouseEventHandler();
    MouseEventHandler(const MouseEventHandler&) = delete;
    MouseEventHandler(MouseEventHandler&&) = delete;
    MouseEventHandler& operator=(const MouseEventHandler&) = delete;
    MouseEventHandler& operator=(MouseEventHandler&&) = delete;
    virtual ~MouseEventHandler();

    ID_t registerMouseButtonPressedCallback(MouseButtonPressedCallback callback);
    ID_t registerMouseButtonReleasedCallback(MouseButtonReleasedCallback callback);

    void bindMouseButtonPress(ID_t button, ID_t callbackID);
    void bindMouseButtonPress(ID_t button, MouseButtonPressedCallback callback);
    void bindMouseButtonRelease(ID_t button, ID_t callbackID);
    void bindMouseButtonRelease(ID_t button, MouseButtonReleasedCallback callback);

    virtual std::vector<std::type_index> getEventTypes() const override;
    virtual void handleEvent(const sf::Event& event) override;

    void operator()(const sf::Event::MouseButtonPressed& event);
    void operator()(const sf::Event::MouseButtonReleased& event);
private:
    std::vector<MouseButtonPressedCallback> m_mouseButtonPressedCallbacks{};
    std::vector<MouseButtonReleasedCallback> m_mouseButtonReleasedCallbacks{};

    std::array<std::vector<ID_t>, MAX_BUTTONS> m_mouseButtonPressBindings{};
    std::array<std::vector<ID_t>, MAX_BUTTONS> m_mouseButtonReleaseBindings{};
}; // class MouseEventHandler

} // namespace Flex