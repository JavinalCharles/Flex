#include <Flex/Core/Error/PathFinderError.hpp>

using namespace flex;

const PathFinderError& flex::pathFinderError() {
	static PathFinderError instance;
	return instance;
}

const char* PathFinderError::name() const noexcept {
	return "PathFinderError";
}

std::string PathFinderError::message(int condition) const {
	switch(static_cast<PFErrorCode>(condition)) {
		case PFErrorCode::PATH_HAS_FILENAME:
			return "Given Path has a file name. Directory required.";
		case PFErrorCode::FILE_NOT_FOUND:
			return "File not found.";
		default:
			return "";
	}
}