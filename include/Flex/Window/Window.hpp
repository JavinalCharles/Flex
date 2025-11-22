#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Window.hpp>
#include <SFML/System.hpp>

#include <string> // IWYU pragma: keep.
#include <variant> // IWYU pragma: keep

#include "Flex/Utilities/Utility.hpp"

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
	template <typename R>
	R getFromKeyOrDefault(const Flex::configMap& configs, const std::string& KEY, const R& defaultValue) {
		return configs.contains(KEY) && std::holds_alternative<R>(configs.at(KEY))
			? std::get<R>(configs.at(KEY)) : defaultValue;
	}

private:
    sf::RenderWindow m_window;
}; // class Window

} // namespace Flex