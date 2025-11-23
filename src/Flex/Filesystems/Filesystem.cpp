#include "Flex/Filesystems/Filesystem.hpp"
#include <cstdlib>
#include <filesystem>

std::string flex::getBasePath() {
    std::filesystem::path exePath;

#ifdef _WIN32
    char buffer[MAX_PATH];
    [[maybe_unused]] DWORD size = GetModuleFileNameA(nullptr, buffer, MAX_PATH);
    exePath = std::filesystem::path(buffer).remove_filename();
#elif __APPLE__
    uint32_t size = 0;
    _NSGetExecutablePath(nullptr, &size); // get required size
    std::string buffer(size, '\0');
    _NSGetExecutablePath(buffer.data(), &size);
    exePath = std::filesystem::canonical(buffer).remove_filename();
#else
    char buffer[PATH_MAX];
    ssize_t len = readlink("/proc/self/exe", buffer, sizeof(buffer) - 1);
    if (len != -1) {
        buffer[len] = '\0';
        exePath = std::filesystem::path(buffer).remove_filename();
    }
#endif

    std::string result = exePath.string();
#ifdef _WIN32
    if (!result.empty() && result.back() != '\\')
        result += '\\';
#else
    if (!result.empty() && result.back() != '/')
        result += '/';
#endif
    return result;
}


std::string flex::getPrefPath(const std::string& org, const std::string& app) {
    std::filesystem::path path;

#ifdef _WIN32
    // Get %APPDATA%
    char* appData = nullptr;
    size_t len = 0;
    _dupenv_s(&appData, &len, "APPDATA");
    if (appData && len > 0) {
        path = std::filesystem::path(appData) / org / app;
        free(appData);
    }
    else {
        // Fallback if APPDATA isn't set
        path = std::filesystem::path(".") / org / app;
    }
#elif __APPLE__
    // ~/Library/Application Support/<app>
    const char* home = std::getenv("HOME");
    if (home)
        path = std::filesystem::path(home) / "Library" / "Application Support" / app;
    else
        path = std::filesystem::path(".") / app;
#else
    // Linux and BSD
    const char* xdgDataHome = std::getenv("XDG_DATA_HOME");
    if (xdgDataHome) {
        path = std::filesystem::path(xdgDataHome) / app;
    }
    else {
        const char* home = std::getenv("HOME");
        if (home)
            path = std::filesystem::path(home) / ".local" / "share" / app;
        else
            path = std::filesystem::path(".") / app;
    }
#endif

    // Create the directory structure if it doesn't exist
    std::filesystem::create_directories(path);

    // Return with trailing slash/backslash like SDL
    std::string result = path.string();
#ifdef _WIN32
    if (!result.empty() && result.back() != '\\')
        result += '\\';
#else
    if (!result.empty() && result.back() != '/')
        result += '/';
#endif
    return result;
}