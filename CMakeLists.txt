cmake_minimum_required(VERSION 3.6)
project(Game-MP-Server)

set(CMAKE_CXX_STANDARD 14)

find_package(SDL2 REQUIRED)
find_package(SDL_net REQUIRED)

include_directories(${SDL2_INCLUDE_DIR})
include_directories(${SDL_NET_INCLUDE_DIR})

set( CMAKE_EXPORT_COMPILE_COMMANDS ON )

file(GLOB_RECURSE SOURCE_FILES
        "src/*.cpp"
        "src/*.h"
        )

add_executable(Game-MP-Server ${SOURCE_FILES})
target_link_libraries(Game-MP-Server ${SDL2_LIBRARIES} ${SDL_NET_LIBRARIES})