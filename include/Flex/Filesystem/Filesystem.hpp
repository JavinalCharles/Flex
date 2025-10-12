#pragma once

#include <iostream>
#include <string>
#include <filesystem>
#include <cstdlib> // for getenv
#ifdef _WIN32
#include <windows.h>
#elif __APPLE__
#include <mach-o/dyld.h>
#else
#include <unistd.h>
#include <limits.h>
#endif

namespace Flex {
    std::string getBasePath();
    std::string getPrefPath(const std::string& org, const std::string& app);
} // namespace Flex