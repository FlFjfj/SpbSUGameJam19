cmake_minimum_required(VERSION 3.6)
project(game)

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(GlUtils)
include_directories(GlUtils)
include_directories(src)
include_directories(GlUtils/ecs)
include_directories(GlUtils/reactphysics3d)

file(GLOB CORE_SOURCE src/*.cpp src/*.h src/utils/*.cpp src/utils/*.h)
add_executable(game ${CORE_SOURCE})
target_link_libraries(game GlUtils)