cmake_minimum_required(VERSION 3.15)

project(
	Flex
	VERSION 0.1
	DESCRIPTION "A Fast And Lightweight Entity Component System (FLECS)-based Game Development Framework built on top of SFML."
	LANGUAGES CXX
)

option(DEBUG "Enables DEBUG_MODE_ON Macro." ON)
option(DEBUG_VERBOSE "Enables DEBUG_VERBOSE_ENABLED" OFF)
option(BUILD_EXAMPLES "Instructs cmake to build the example programs as well, after building the library" OFF)


if(DEBUG)
	add_compile_definitions(DEBUG_MODE_ON)
	if(DEBUG_VERBOSE)
		add_compile_definitions(DEBUG_VERBOSE_ENABLED)
	endif()
endif()

# Project-wide C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Collect source files from src/
file(GLOB_RECURSE FLEX_SOURCES
	"${PROJECT_SOURCE_DIR}/src/*.cpp"
	"${PROJECT_SOURCE_DIR}/src/*.cxx"
	"${PROJECT_SOURCE_DIR}/src/*.cc"
	"${PROJECT_SOURCE_DIR}/src/*.c"
)

if(NOT FLEX_SOURCES)
	message(FATAL_ERROR "No source files found in ${PROJECT_SOURCE_DIR}/src. Make sure the `src/` directory contains .cpp or .cxx files.")
endif()

# Create static library target
add_library(Flex STATIC ${FLEX_SOURCES})

# Public include directory
target_include_directories(Flex
	PUBLIC
		$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
		$<INSTALL_INTERFACE:include>
)

# Use modern CMake feature requirement
target_compile_features(Flex PUBLIC cxx_std_20)

# Compiler warning flags (portable)
if(MSVC)
	target_compile_options(Flex PRIVATE /W4 /permissive-)
else()
	target_compile_options(Flex PRIVATE -Wall -Wextra -Wshadow -Wunused -Wno-unused-parameter)
	# Optimize for release by default; users can override CMAKE_BUILD_TYPE
	if(NOT CMAKE_BUILD_TYPE)
		set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Build type" FORCE)
	endif()
endif()

# Expose debug macros to target if requested
if(DEBUG)
	target_compile_definitions(Flex PUBLIC DEBUG_MODE_ON)
	if(DEBUG_VERBOSE)
		target_compile_definitions(Flex PUBLIC DEBUG_VERBOSE_ENABLED)
	endif()
endif()

# Install rules (optional)
install(TARGETS Flex
	EXPORT FlexTargets
	ARCHIVE DESTINATION lib
	LIBRARY DESTINATION lib
	RUNTIME DESTINATION bin
)

install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/ DESTINATION include)

# Export package config if desired
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
	"${CMAKE_CURRENT_BINARY_DIR}/FlexConfigVersion.cmake"
	VERSION ${PROJECT_VERSION}
	COMPATIBILITY AnyNewerVersion
)


