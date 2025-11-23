#include "Flex/Core/Flex.hpp"
#include "SFML/Window/Event.hpp"
#include <chrono>
#include <iostream>
#include <optional>
#include <system_error>
#include <thread>

#include "Flex/Events/Types/KeyboardEvents.hpp"
#include "Flex/Events/Types/MouseEvents.hpp"

namespace fs = std::filesystem;

namespace flex {

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

void Flex::setDefaultConfigFunction(std::function<void(configMap&)> callable) {
	m_defaultConfigFunction = callable;
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
	const int FPS_LIMIT = getFPSLimit();
	const double TARGET_FRAME_TIME = 1.0 / static_cast<double>(FPS_LIMIT);
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
	saveConfig();
}

void Flex::handleEvents() {
	m_window.getRenderWindow().handleEvents(
		[&](const sf::Event::Closed&) {
			m_window.close();
		},
		[&](const sf::Event::KeyPressed& e) {
			m_world.handleEvent(KeyPressedEvent(e));
		},
		[&](const sf::Event::KeyReleased& e) {
			m_world.handleEvent(KeyReleasedEvent(e));
		},
		[&](const sf::Event::MouseButtonPressed& e) {
			m_world.handleEvent(MouseButtonPressedEvent(e));
		},
		[&](const sf::Event::MouseButtonReleased& e) {
			m_world.handleEvent(MouseButtonReleasedEvent(e));
		},
		[&](const sf::Event::MouseWheelScrolled& e) {
			m_world.handleEvent(MouseWheelScrolledEvent(e));
		}
	);
}

void Flex::update(double dt) {
	// Update game logic here
}

void Flex::postUpdate(double dt) {
	// Post-update logic here
}

void Flex::draw() {
	if (!m_window.isOpen())
		return;
	sf::RenderWindow& window = m_window.getRenderWindow();
	window.clear(sf::Color::Black);
	// Draw your game objects here
	window.display();
}

int Flex::getFPSLimit() const {
	auto it = m_config.find("window_framerate_limit");
	return it != m_config.end() && std::holds_alternative<int>(it->second) ? std::get<int>(it->second) : 60;
}


void Flex::resetConfigDefaults() {
	if (m_defaultConfigFunction != nullptr) {
		m_defaultConfigFunction(m_config);
	}
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
		if (key == nullptr) {
			continue;
		}

		const std::string strKey(key);
	
		int* intValue = nullptr;
		double* doubleValue = nullptr;
		const char* strValue = nullptr;
		if (elem->QueryIntAttribute("value", intValue) == tinyxml2::XML_SUCCESS) {
			m_config.insert_or_assign(strKey, *intValue);
		}
		else if (elem->QueryDoubleAttribute("value", doubleValue) == tinyxml2::XML_SUCCESS) {
			m_config.insert_or_assign(strKey, *doubleValue);
		}
		else if (elem->QueryStringAttribute(key, &strValue) == tinyxml2::XML_SUCCESS) {
			m_config.insert_or_assign(strKey, std::string(strValue));
		}
	}
	m_config["config_path"] = configPath.string();
}

namespace {
	struct ConfigValueVisitor {
		std::string operator()(int value) {
			return std::to_string(value);
		}
		std::string operator()(double value) {
			return std::to_string(value);
		}
		std::string operator()(const std::string& value) {
			return value;
		}
	};
}

void Flex::saveConfig() {
	auto it = m_config.find("config_path");
	if (it == m_config.end() || !std::holds_alternative<std::string>(it->second))
		return;

	const std::string configLoc = std::get<std::string>(it->second);
	m_config.erase(it);

	tinyxml2::XMLDocument newXMLDocument;
	tinyxml2::XMLElement* newRoot = static_cast<tinyxml2::XMLElement*>(m_xmlDoc.RootElement()->ShallowClone(&newXMLDocument));

	ConfigValueVisitor visitor;

	for (const auto& [key, v] : m_config) {
		tinyxml2::XMLElement* elem = newRoot->InsertNewChildElement("config");
		std::string value = std::visit(visitor, v);
		elem->SetAttribute("key", key.c_str());
		elem->SetAttribute("value", value.c_str());
	}

	newXMLDocument.SaveFile(configLoc.c_str());
}

} // namespace flex