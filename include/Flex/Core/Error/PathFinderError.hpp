#pragma once

#include <string>
#include <system_error>

namespace flex {

enum class PFErrorCode : int {
	PF_NO_ERROR = 0,
	PATH_HAS_FILENAME,
	FILE_NOT_FOUND,
};

class PathFinderError : public std::error_category {
public:
	const char* name() const noexcept override;

	std::string message(int condition) const override;
}; // class PathFinderError



const PathFinderError& pathFinderError();

} // namespace flex

namespace std {
    template <>
    struct std::is_error_code_enum<Flex::PFErrorCode> : std::true_type {};
}