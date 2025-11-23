#pragma once

#include <string>

#ifdef _WIN32
#include <windows.h>
#elif __APPLE__
#include <mach-o/dyld.h>
#else
#include <unistd.h>
#include <limits.h>
#endif

namespace flex {
    std::string getBasePath();
    std::string getPrefPath(const std::string& org, const std::string& app);
} // namespace flex