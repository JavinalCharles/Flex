#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Window.hpp>
#include <SFML/System.hpp>

#include <string>

#include "Flex/Utility/Utility.hpp"

namespace Flex {

class Window {
public:
    Window();
    Window(const Window&) = delete;
    Window(Window&&) = delete;
    Window& operator=(const Window&) = delete;
    Window& operator=(Window&&) = delete;
    virtual ~Window();

    void create(const configMap& configs);
    // void create(const sf::VideoMode& mode, const std::string& title, sf::Uint32 style = sf::Style::Default, const sf::ContextSettings& settings = sf::ContextSettings());
    void close();
    bool isOpen() const;

    sf::Vector2u getSize() const;
    sf::Vector2i getPosition() const;
    void setPosition(const sf::Vector2i& position);
    void setSize(const sf::Vector2u& size);

    sf::RenderWindow& getRenderWindow();
    const sf::RenderWindow& getRenderWindow() const;
private:
    sf::RenderWindow m_window;
}; // class Window

} // namespace Flex