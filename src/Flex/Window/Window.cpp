#include "Flex/Window/Window.hpp"

using Flex::Window;

Window::Window() = default;

Window::~Window() = default;

void Window::create(const configMap& configs) {
    std::string title = configs.contains("title") ? std::get<std::string>(configs.at("title")) : "Flex App";
    unsigned int width = configs.contains("width") ? std::get<int>(configs.at("width")) : 800;
    unsigned int height = configs.contains("height") ? std::get<int>(configs.at("height")) : 600;
    bool fullscreen = configs.contains("fullscreen") ? static_cast<bool>(std::get<int>(configs.at("fullscreen"))) : false;
    bool vsync = configs.contains("vsync") ? static_cast<bool>(std::get<int>(configs.at("vsync"))) : false;
    unsigned int framerateLimit = configs.contains("framerate_limit") ? std::get<int>(configs.at("framerate_limit")) : 60;
    unsigned int antialiasingLevel = configs.contains("antialiasing_level") ? std::get<int>(configs.at("antialiasing_level")) : 0;
    unsigned int majorVersion = configs.contains("major_version") ? std::get<int>(configs.at("major_version")) : 0;
    unsigned int minorVersion = configs.contains("minor_version") ? std::get<int>(configs.at("minor_version")) : 0;

    sf::VideoMode videoMode(sf::Vector2u(width, height));
    sf::State state = fullscreen ? sf::State::Fullscreen : sf::State::Windowed;

    std::uint32_t style = sf::Style::Default;

    sf::ContextSettings settings;
    settings.antiAliasingLevel = antialiasingLevel;
    settings.majorVersion = majorVersion;
    settings.minorVersion = minorVersion;

    m_window.create(videoMode, title, style, state, settings);
    m_window.setVerticalSyncEnabled(vsync);
    m_window.setFramerateLimit(framerateLimit);
}

void Window::close() {
    m_window.close();
}

bool Window::isOpen() const {
    return m_window.isOpen();
}

sf::Vector2u Window::getSize() const {
    return m_window.getSize();
}

sf::Vector2i Window::getPosition() const {
    return m_window.getPosition();
}

void Window::setPosition(const sf::Vector2i& position) {
    m_window.setPosition(position);
}

void Window::setSize(const sf::Vector2u& size) {
    m_window.setSize(size);
}

sf::RenderWindow& Window::getRenderWindow() {
    return m_window;
}

const sf::RenderWindow& Window::getRenderWindow() const {
    return m_window;
}