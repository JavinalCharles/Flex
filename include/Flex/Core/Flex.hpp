#pragma once

#include "tinyxml2/tinyxml2.h"
#include "Flex/Core/PathFinder.hpp"

namespace fs = std::filesystem;

namespace Flex {

class Flex {
public:
	/**
	 * @brief Construct a new Flex object
	 * 
	 */
	/// @{
	Flex();

	Flex(const Flex&) = delete;
	Flex(Flex&&) = delete;
	Flex& operator=(const Flex&) = delete;
	Flex& operator=(Flex&&) = delete;
	/// @}

	/// @brief Destructor
	virtual ~Flex();

	/**
	 * @name Flex::init()
	 * @brief initializes the Flex object in preparation for the
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
private:
	void handleEvents();
	void update(float dt);
	void postUpdate(float dt);
	void draw();

	void cleanUp();
private:
	PathFinder m_pf;
}; // class Engine

} // namespace Flex