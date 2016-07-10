cmake_minimum_required(VERSION 2.8.12)
project(YayEvil)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

if (NOT NO_COTIRE)
include(cmake/cotire.cmake)
endif()

if (NOT WINSIMPLE)
find_package(SDL2 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(Freetype REQUIRED)
find_package(SDL2Image REQUIRED)

include_directories(${SDL2_INCLUDE_DIR})
include_directories(${OPENGL_INCLUDE_DIR})
include_directories(${GLEW_INCLUDE_DIR})
include_directories(${FREETYPE_INCLUDE_DIR_ft2build})
include_directories(${SDL2IMAGE_INCLUDE_DIR})
endif()

if (WINSIMPLE)
add_definitions(-DWINSIMPLE=1)
include_directories(${INCLUDE_DIR})
link_directories(${LIBRARY_DIR})
endif()

add_subdirectory(src)




