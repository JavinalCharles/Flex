#include "Flex/Core/Flex.hpp"
#include <iostream>

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

}

void Flex::init(const std::string& configFile) {
	init(fs::path(configFile));
}

void Flex::init(const fs::path& configPath) {
	std::optional<fs::path> p = m_pf.find(configPath);
	if (!p.has_value())
		return;
	// TODO: Load and map the configurations
}

} // namespace Flex