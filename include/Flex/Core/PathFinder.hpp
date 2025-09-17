#pragma once

#include <array>
#include <filesystem>
#include <optional>
#include <vector>

#include <Flex/Core/Error/PathFinderError.hpp>

using std::filesystem::path;
using std::string;

namespace Flex {

/**
 * @brief An object that finds path in the file system.
 * @details An object of type PathFinder can traverse the file system
 * in search of a specific resource or file relative to a directory or an
 * array of directories from which the PathFinder shall begin its search
 * before eventually returning with an absolute path to the required
 * resource, or a null value.
 * @author Charlemagne Javinal
 * @copyright MIT License
 * 
 */
class PathFinder {
 public:
	/// @brief PathFinder constructor
	PathFinder() noexcept;

	virtual ~PathFinder();

	/** 
	 * @name PathFinder::addBaseDirectory
	 * @brief Adds a path to this PathFinder's array of prefix directories
	 * @details The added paths will be used as a basis for which
	 * PathFinder will use as a basis for its recursive search in the
	 * file system.
	 * @param basePrefixPath The prefix path to be added.
	 * @return For the non-void overloadss, returns non-zero integer in 
	 * failure. 0 otherwize.
	 */
	/// @{
	// int addBaseDirectory(const string& basePrefixStr) noexcept;
	int addBaseDirectory(const path& basePrefixPath) noexcept;
	// void addBaseDirectory(const string& basePrefixStr, std::error_code& ec) noexcept;
	void addBaseDirectory(const path& newPrefixPath, std::error_code& ec) noexcept;
	/// @}

	/**
	 * @name PathFinder::find
	 * @brief Recurively searches the base paths for a specified file.
	 * @details The PathFinder recursively searches the base paths for a
	 * specific paths that ends with filePath or fileStr. In cases where
	 * multiple filePath or fileStr exists, returns the first one found as
	 * decided by std::recursive_directory_iterator, skipping those with
	 * denied permissions.
	 * The method will return a nullopt in cases:
	 * - fileStr/filePath is empty or does not end in a file name.
	 * - There are problems with the storage disc.
	 * - The base paths itselves has denied permissions.
	 * - fileStr/filePath is malformed/contains invalid characters.
	 * 
	 * @param filePath the path of the desired file
	 * @param basePath find will only search under this path.
	 * @param ec Error code to pass on error messages in the event of failure.
	 * @returns An absolute path to the first existing file with that matches 
	 * the given fileStr or filePath, or nullopt in case of failure.
	 */
	/// @{
	// std::optional<path> find(const string& fileStr) const noexcept;
	std::optional<path> find(const path& filePath) const noexcept;
	// std::optional<path> find(const string& fileStr, std::error_code& ec) const noexcept;
	std::optional<path> find(const path& filePath, std::error_code& ec) const noexcept;
	// TODO: static overloads!
	static std::optional<path> find(const path& filePath, const path& basePath) noexcept;
	static std::optional<path> find(const path& filePath, const path& basePath, std::error_code& ec) noexcept;
	/// @}

public:
	/**
	 * @name PathFinder::addCommonDirectory
	 * @brief Adds a path accessible to all instances of PathFinders.
	 * @details Similar to the PathFinder::addBaseDirectory(), but any path
	 * added here will be available to all instances of PathFinders as well as
	 * any types derived from PathFinder class for their respective search for
	 * file system paths.
	 * 
	 * @param dirPath the path to be added.
	 */
	/// @{
	// static int addCommonDirectory(const string& dirStr) noexcept;
	static int addCommonDirectory(const path& dirPath) noexcept;
	// static void addCommonDirectory(const string& dirStr, std::error_code& ec) noexcept;
	static void addCommonDirectory(const path& dirPath, std::error_code& ec) noexcept;
	/// @}

private:
	static std::optional<path> findHelper(const path& BASE, const path& TARGETFILE, std::error_code& ec) noexcept;

private:
	std::vector<path> m_baseDirs;

	static std::vector<path> s_commonDirs;
}; // class PathFinder

} // namespace Flex