cmake_minimum_required(VERSION 2.8)

project(minigame)

FIND_PACKAGE(PkgConfig REQUIRED)

INCLUDE(FindPkgConfig)

PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)

FIND_PACKAGE(OpenGL REQUIRED)
FIND_PACKAGE(GLEW REQUIRED)
FIND_PACKAGE(PNG REQUIRED)
FIND_PACKAGE(Freetype REQUIRED)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra")

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_DEBUG} -g -O0 -DDEBUG")

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_RELEASE} -O2")

add_subdirectory("${PROJECT_SOURCE_DIR}/src")

add_subdirectory("${PROJECT_SOURCE_DIR}/src/renderer")

add_subdirectory("${PROJECT_SOURCE_DIR}/src/entity")

add_subdirectory("${PROJECT_SOURCE_DIR}/src/window")

add_subdirectory("${PROJECT_SOURCE_DIR}/src/camera")

add_subdirectory("${PROJECT_SOURCE_DIR}/src/resources")

add_subdirectory("${PROJECT_SOURCE_DIR}/src/debug")

add_subdirectory("${PROJECT_SOURCE_DIR}/src/defs")

add_subdirectory("${PROJECT_SOURCE_DIR}/src/exceptions")

add_subdirectory("${PROJECT_SOURCE_DIR}/src/math")

add_subdirectory("${PROJECT_SOURCE_DIR}/src/mesh")

add_subdirectory("${PROJECT_SOURCE_DIR}/src/program")

add_subdirectory("${PROJECT_SOURCE_DIR}/src/sprite")

add_subdirectory("${PROJECT_SOURCE_DIR}/src/text")

add_subdirectory("${PROJECT_SOURCE_DIR}/src/texture")

add_subdirectory("${PROJECT_SOURCE_DIR}/src/utils")

add_subdirectory("${PROJECT_SOURCE_DIR}/src/input")

add_subdirectory("${PROJECT_SOURCE_DIR}/src/controller")

add_subdirectory("${PROJECT_SOURCE_DIR}/test")

INCLUDE_DIRECTORIES(
  ${SDL2_INCLUDE_DIRS}
  ${SDL2IMAGE_INCLUDE_DIRS}
  ${OPENGL_INCLUDE_DIR}
  ${GLEW_INCLUDE_DIR}
  ${PNG_INCLUDE_DIR}
  ${FREETYPE_INCLUDE_DIRS})

ADD_EXECUTABLE(${PROJECT_NAME} ${SOURCE} ${HEADERS})

TARGET_LINK_LIBRARIES(
  ${PROJECT_NAME}
  ${SDL2_LIBRARIES}
  ${SDL2IMAGE_LIBRARIES}
  ${OPENGL_LIBRARIES}
  ${GLEW_LIBRARIES}
  ${PNG_LIBRARIES}
  ${FREETYPE_LIBRARIES})