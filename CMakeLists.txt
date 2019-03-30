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

file(GLOB CORE_SOURCE
  src/*.cpp src/*.h
  src/utils/*.cpp src/utils/*.h
  src/game/*.cpp src/game/*.h
)

file (GLOB_RECURSE MENU_SCENES
  src/game/scenes/menu/*.cpp
  src/game/scenes/menu/*.h
)

file (GLOB_RECURSE TEST_FILES
  src/game/scenes/test/*.cpp
  src/game/scenes/test/*.h
)

file (GLOB_RECURSE EPISODES_FILES
        src/game/scenes/episodes/*.cpp
        src/game/scenes/episodes/*.h
        )

add_executable(game ${CORE_SOURCE} ${MENU_SCENES} ${TEST_FILES} ${EPISODES_FILES})
target_link_libraries(game GlUtils)
