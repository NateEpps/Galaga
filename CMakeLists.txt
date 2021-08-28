#
# CMakeLists.txt - Galaga
# Nathanael Epps
#
# The main build script for the project, requires CMake >= 3.1 and SFML >= 2.5.
#

cmake_minimum_required(VERSION 3.1)

project(Galaga VERSION 0.7)

# Find SFML
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

# Debug/Release
if (NOT CMAKE_BUILD_TYPE)
   set(CMAKE_BUILD_TYPE Debug)
endif ()

message(STATUS "CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}")

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG -g")

# Add source
add_subdirectory(${CMAKE_SOURCE_DIR}/src/)

# Compile
set(CMAKE_CXX_STANDARD 14)

include_directories(${SFML_INCLUDE_DIR} ${CMAKE_SOURCE_DIR}/src/ ${CMAKE_BINARY_DIR})

add_executable(Galaga ${SourceCode})
add_library(Galaga-Rss STATIC ${ResourceCode})

# Link
target_link_libraries(Galaga Galaga-Rss sfml-graphics sfml-window sfml-system)

# Write Configuration file - depends on compile step
message(STATUS "Writing ${CMAKE_BINARY_DIR}/Config.hpp...")

configure_file(${CMAKE_SOURCE_DIR}/src/Config.hpp.in ${CMAKE_BINARY_DIR}/Config.hpp)