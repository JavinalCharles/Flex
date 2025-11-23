#include "Flex/Window/Window.hpp"

using flex::Window;

Window::Window() = default;

Window::~Window() = default;

namespace {
	const std::string WIN_TITLE = "window_title";
	const std::string WIN_WIDTH = "window_width";
	const std::string WIN_HEIGHT = "window_height";
	const std::string WIN_FULLSCREEN = "window_fullscreen";
	const std::string WIN_VSYNC = "window_vsync";
	const std::string WIN_FPS_LIMIT = "window_framerate_limit";
	const std::string WIN_ANTIALIASING_LVL = "window_antialiasing_level";
	const std::string WIN_MAJOR_VERSION = "window_major_version";
	const std::string WIN_MINOR_VERSION = "window_minor_version";
}

void Window::create(const configMap& configs) {
	const std::string TITLE = getFromKeyOrDefault<std::string>(configs, WIN_TITLE, "FLEX App");
	const size_t WIDTH = getFromKeyOrDefault<int>(configs, WIN_WIDTH, 800);
	const size_t HEIGHT = getFromKeyOrDefault<int>(configs, WIN_HEIGHT, 600);
	const bool FULLSCREEN_ON = getFromKeyOrDefault<int>(configs, WIN_FULLSCREEN, 0);
	const bool VSYNC_ENABLED = getFromKeyOrDefault<int>(configs, WIN_VSYNC, 0);
    const size_t FPS_LIMIT = getFromKeyOrDefault(configs, WIN_FPS_LIMIT, 0);
    const size_t ANTIALIASING_LVL = getFromKeyOrDefault(configs, WIN_ANTIALIASING_LVL, 0);
    const size_t MAJOR_VERSION = getFromKeyOrDefault(configs, WIN_MAJOR_VERSION, 0);
    const size_t MINOR_VERSION = getFromKeyOrDefault(configs, WIN_MINOR_VERSION, 1);

    sf::VideoMode videoMode(sf::Vector2u(WIDTH, HEIGHT));
    sf::State state = FULLSCREEN_ON ? sf::State::Fullscreen : sf::State::Windowed;

    std::uint32_t style = sf::Style::Default;

    sf::ContextSettings settings;
    settings.antiAliasingLevel = ANTIALIASING_LVL;
    settings.majorVersion = MAJOR_VERSION;
    settings.minorVersion = MINOR_VERSION;

    m_window.create(videoMode, TITLE, style, state, settings);
	if (VSYNC_ENABLED)
    	m_window.setVerticalSyncEnabled(VSYNC_ENABLED);
	else if (FPS_LIMIT > 0)
    	m_window.setFramerateLimit(FPS_LIMIT);
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