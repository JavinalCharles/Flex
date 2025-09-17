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

set(SOURCES
	
)

add_library(compiler_flags INTERFACE)
target_compile_features(compiler_flags INTERFACE cxx_std_20)
target_compile_options(compiler_flags INTERFACE 
	"$<BUILD_INTERFACE:-Wall;-Wextra;-Wshadow;-Wunused;-Wno-unused-parameter;-O2>"
)

add_library(flex STATIC ${SOURCES})

target_include_directories(flex
	PUBLIC
	${PROJECT_SOURCE_DIR}/include/
)


