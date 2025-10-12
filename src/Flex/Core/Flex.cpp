#include "Flex/Core/Flex.hpp"
#include <iostream>

namespace fs = std::filesystem;

namespace Flex {

Flex::Flex() {
	std::error_code ec;
	const fs::path CWD(fs::current_path(ec));
	if (ec)
		std::cerr << "Unable to find CWD." << std::endl;
	else
		m_pf.addCommonDirectory(CWD);
}

Flex::~Flex() { 
	cleanUp();
}

void Flex::init() {
	resetConfigDefaults();
}

void Flex::init(const std::string& configFile) {
	resetConfigDefaults();
	init(fs::path(configFile));
}

void Flex::init(const std::filesystem::path& configPath) {
	std::optional<fs::path> p = m_pf.find(configPath);
	if (!p.has_value())
		return;
	// TODO: Load and map the configurations
	readAndMapConfigs(p.value());
	m_window.create(m_config);
}

inline void preciseSleep(double seconds) {
	using clock = std::chrono::steady_clock;
	auto start = clock::now();
	auto end = start + std::chrono::duration<double>(seconds);
	double sleepTime = seconds - 0.001; // Sleep for slightly less than the target time
	if (sleepTime > 0.0	) {
		std::this_thread::sleep_for(std::chrono::duration<double>(sleepTime));
	}
	while (clock::now() < end) {
		// Busy-waiting for the remaining time
	}
}

void Flex::run() {
	
	const double TARGET_FPS = 1.0 / std::get<int>(m_config["framerate_limit"]);
	const double TARGET_FRAME_TIME = 1.0 / TARGET_FPS;
	sf::Clock clock;
	
	auto previous = std::chrono::steady_clock::now();
	
	m_isRunning = true;

	while (m_window.isOpen()) {
		handleEvents();

		auto frameStart = std::chrono::steady_clock::now();
		std::chrono::duration<double> elapsed = frameStart - previous;
		previous = frameStart;

		// Update game logic with elapsed time
		double dt = elapsed.count();
		update(dt);
		postUpdate(dt);

		// Render the frame
		draw();

		// Frame pacing
		auto frameEnd = std::chrono::steady_clock::now();
		std::chrono::duration<double> frameDuration = frameEnd - frameStart;
		double sleepTime = TARGET_FRAME_TIME - frameDuration.count();
		if (sleepTime > 0.0) {
			preciseSleep(sleepTime);
		}
	}

	m_isRunning = false;
	m_window.close();
}

void Flex::handleEvents() {
	std::optional<sf::Event> event;
	while (event = m_window.getRenderWindow().pollEvent()) {
		if (event->is<sf::Event::Closed>()) {
			m_window.close();
			break;
		}
	}
}


void Flex::resetConfigDefaults() {
	std::string temp = m_config.contains("title") ? std::get<std::string>(m_config["title"]) : "Flex App";
	m_config.clear();
	m_config["title"] = temp;
	m_config["width"] = 800;
	m_config["height"] = 600;
	m_config["fullscreen"] = 0;
	m_config["antialiasing_level"] = 0;
	m_config["vsync"] = 1;
	m_config["framerate_limit"] = 60;
}

void Flex::readAndMapConfigs(const fs::path& configPath) {
	tinyxml2::XMLError err = m_xmlDoc.LoadFile(configPath.string().c_str());
	if (err != tinyxml2::XML_SUCCESS) {
		std::cerr << "Error: Unable to load config file: " << configPath << std::endl;
		return;
	}
	tinyxml2::XMLElement* root = m_xmlDoc.RootElement();
	if (!root) {
		std::cerr << "Error: Config file is empty or malformed." << std::endl;
		return;
	}
	// Example: Parse key-value pairs from XML
	for (tinyxml2::XMLElement* elem = root->FirstChildElement("config"); elem != nullptr; elem = elem->NextSiblingElement("config")) {
		const char* key = elem->Attribute("key");
		int value = elem->IntAttribute("value");
		if (key) {
			m_config[key] = value;
		}
	}
}

} // namespace Flex