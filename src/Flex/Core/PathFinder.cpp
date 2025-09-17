#include <Flex/Core/PathFinder.hpp>
#include <iostream>

using namespace Flex;
namespace fs = std::filesystem;

namespace {
	constexpr std::string_view HAS_FILENAME = "The provided prefix path has a file name: ";
}

std::vector<fs::path> PathFinder::s_commonDirs;

PathFinder::PathFinder() noexcept = default;

PathFinder::~PathFinder() {}

// int PathFinder::addBaseDirectory(const string& basePrefixStr) noexcept {
// 	std::error_code ec;
// 	addBaseDirectory(fs::path(basePrefixStr), ec);
// 	return ec.value();
// }

int PathFinder::addBaseDirectory(const fs::path& basePrefixPath) noexcept {
	std::error_code ec;
	addBaseDirectory(basePrefixPath, ec);
	return ec.value();
}

// void PathFinder::addBaseDirectory(const string& basePrefixStr, std::error_code& ec) noexcept {
// 	addBaseDirectory(fs::path(basePrefixStr), ec);
// }

void PathFinder::addBaseDirectory(const fs::path& dirPath, std::error_code& ec) noexcept {
	fs::path canonPath(fs::canonical(dirPath, ec));
	if (ec.value() != 0) return;

	if (fs::is_regular_file(canonPath, ec)) {
		if (ec.value() != 0)
			ec.assign(static_cast<int>(Flex::PFErrorCode::PATH_HAS_FILENAME), pathFinderError());
		return;
	}
	try { m_baseDirs.push_back(canonPath); }
	catch (const std::exception& e) { return; }

	ec.clear();
}

// std::optional<fs::path> PathFinder::find(const std::string& str) const noexcept {
// 	std::error_code ec;
// 	return find(fs::path(str), ec);
// }

std::optional<fs::path> PathFinder::find(const fs::path& file) const noexcept {
	std::error_code ec;
	return find(file, ec);
}

// std::optional<fs::path> PathFinder::find(const std::string& str, std::error_code& ec) const noexcept {
// 	return find(path(str), ec);
// }

std::optional<fs::path> PathFinder::find(const fs::path& file, std::error_code& ec) const noexcept {
	if (file.is_absolute()) {
		if (std::filesystem::exists(file, ec)) {
			return std::make_optional(file);
		}
		if (ec.value() == 0) 
			ec.assign(static_cast<int>(Flex::PFErrorCode::FILE_NOT_FOUND), pathFinderError());
		return std::nullopt;
	}
	for (const auto& baseDir : m_baseDirs) {
		std::optional<fs::path> res = findHelper(baseDir, file, ec);
		if (res.has_value()) return res;
		if (ec) {
			std::cerr << ec.message() << std::endl;
			ec.clear();
		}
	}
	// The instance-specific base dirs does not have the target file. 
	// Searc within the common dirs.
	for (const auto& baseDir : s_commonDirs) {
		std::optional<fs::path> res = findHelper(baseDir, file, ec);
		if (res.has_value()) return res;
		if (ec) {
			std::cerr << ec.message() << std::endl;
			ec.clear();
		}
	}

	ec.assign(static_cast<int>(PFErrorCode::FILE_NOT_FOUND), pathFinderError());

	return std::nullopt;
}

std::optional<fs::path> PathFinder::find(const fs::path& file, const fs::path& prefix) noexcept {
	std::error_code ec;
	return PathFinder::find(file, prefix, ec);
}

std::optional<fs::path> PathFinder::find(const fs::path& file, const fs::path& prefix, std::error_code& ec) noexcept {
	if (file.is_absolute()) {
		if (std::filesystem::exists(file, ec)) {
			return std::make_optional(file);
		}
		if (ec.value() == 0) 
			ec.assign(static_cast<int>(Flex::PFErrorCode::FILE_NOT_FOUND), pathFinderError());
		return std::nullopt;
	}
	return findHelper(prefix, file, ec);
}

int PathFinder::addCommonDirectory(const fs::path& dirPath) noexcept {
	std::error_code ec;
	addCommonDirectory(dirPath, ec);
	return ec.value();
}

void PathFinder::addCommonDirectory(const fs::path& dirPath, std::error_code& ec) noexcept {
	fs::path canonPath(fs::absolute(dirPath, ec));
	if (ec.value() != 0) return;

	if (fs::is_regular_file(canonPath, ec)) {
		if (ec.value() != 0)
			ec.assign(static_cast<int>(Flex::PFErrorCode::PATH_HAS_FILENAME), pathFinderError());
		return;
	}

	try { s_commonDirs.push_back(canonPath); }
	catch (const std::exception& e) { return; }

	ec.clear();
}

std::optional<fs::path> PathFinder::findHelper(const fs::path& BASE, const fs::path& TARGETFILE, std::error_code& ec) noexcept {
	constexpr fs::directory_options option = fs::directory_options::follow_directory_symlink | fs::directory_options::skip_permission_denied;

	const fs::path::string_type& TARGET = TARGETFILE.native();
	fs::recursive_directory_iterator iter(BASE, option, ec);

	if (ec) return std::nullopt;

	for (const fs::directory_entry& entry : iter) {
		if (false == entry.is_regular_file(ec)) {
			if (ec) {
				std::cerr << ec.message() << std::endl;
				ec.clear();
			}
		}
		else {
			const fs::path& entryPath = entry.path();
			if (entryPath.native().ends_with(TARGET))
				return std::optional<fs::path>(entryPath);
		}
	}
	return std::nullopt;
}