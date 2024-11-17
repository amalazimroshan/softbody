cmake_minimum_required(VERSION 3.20)
project(softbody)

set(CMAKE_CXX_STANDARD 20)

# Find SDL2 and SDL2_ttf
find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)

# Glob headers and sources
file(GLOB_RECURSE SOFTBODY_HEADERS "include/*.hpp")
file(GLOB_RECURSE SOFTBODY_SOURCES "source/*.cpp")

# Set build type and flags
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -pg -O0")

# Define the executable
add_executable(softbody
    ${SOFTBODY_HEADERS}
    ${SOFTBODY_SOURCES}
)

# Include directories
target_include_directories(softbody PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
    ${SDL2_INCLUDE_DIRS}
    ${SDL2_TTF_INCLUDE_DIRS}
)

# Link libraries
target_link_libraries(softbody PUBLIC
    ${SDL2_LIBRARIES}
    ${SDL2_TTF_LIBRARIES}
)
