#
# src/CMakeLists.txt
#

file(GLOB SRC "*.*pp")
file(GLOB RSS "${CMAKE_SOURCE_DIR}/src/rss/*.*pp")

message(STATUS "Found source code in ${CMAKE_CURRENT_SOURCE_DIR}")

set(SourceCode ${SRC} PARENT_SCOPE)
set(ResourceCode ${RSS} PARENT_SCOPE)
