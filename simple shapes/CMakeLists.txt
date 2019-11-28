cmake_minimum_required(VERSION 3.2)

project(simple-shapes)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
find_package(SFML COMPONENTS network audio graphics window system REQUIRED)
find_package(Box2D REQUIRED)



if(BOX2D_FOUND)
    include_directories(${BOX2D_INCLUDE_DIR})
endif()

add_subdirectory(src)
