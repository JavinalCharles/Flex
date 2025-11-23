#pragma once

#include <filesystem>
#include <string>
// #include <unordered_map>
// #include <variant>

#include <tinyxml2/tinyxml2.h>
#include <Flex/Filesystems/PathFinder.hpp>
#include <Flex/Scenes/SceneManager.hpp>

#include <SFML/Window/Event.hpp>

#include "Flex/Core/Worlds//World.hpp"
#include "Flex/Utilities/Utility.hpp"
#include "Flex/Window/Window.hpp"

namespace fs = std::filesystem;
using flex::Window;

namespace flex {

class Flex {
public:
	/**
	 * @brief Construct a new flex object
	 * 
	 */
	/// @{
	Flex();

	Flex(const flex&) = delete;
	Flex(Flex&&) = delete;
	Flex& operator=(const flex&) = delete;
	Flex& operator=(Flex&&) = delete;
	/// @}

	/// @brief Destructor
	virtual ~Flex();

	/// 
	/// @brief Set the Default Config Function of the app.
	/// 
	/// @param callable The function
	///
	/// Should be used to initialize each configuration's default values
	/// when the application is first ran, or when the user elects to
	/// to "reset settings to default".
	///
	void setDefaultConfigFunction(std::function<void(configMap&)> callable);

	/**
	 * @name flex::init()
	 * @brief initializes the flex object in preparation for the
	 * game loop.
	 * 
	 * @param configFile filename of the config file.
	 * @param configPath path to the config file.
	 */
	/// @{
	void init();
	void init(const std::string& configFile);
	void init(const fs::path& configPath);
	/// @}

	void run();

	PathFinder& getPF();
	const PathFinder getPF() const;
private: // GAME LOOP
	void handleEvents();
	void update(double dt);
	void postUpdate(double dt);
	void draw();

private: // HELPERS
	void readAndMapConfigs(const fs::path& configPath);
	void resetConfigDefaults();

	void cleanUp();
private:
	bool m_isRunning = false;

	World m_world;
	// std::unordered_map<std::string, std::variant>

	Window m_window;
	SceneManager m_sceneManager;
	PathFinder m_pf;

	configMap m_config;
	std::function<void(configMap&)> m_defaultConfigFunction;

	tinyxml2::XMLDocument m_xmlDoc;
}; // class Flex

} // namespace flex