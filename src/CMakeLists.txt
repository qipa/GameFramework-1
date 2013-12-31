#要求するcmakeのバージョン
cmake_minimum_required(VERSION 2.8)

#project name

PROJECT(Syukatsu)
file(GLOB srcFile ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

#c++0x対応オプション
set(CMAKE_CXX_FLAGS_RELEASE "-Wall -O2")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS "-std=c++0x") 

set(CMAKE_BUILD_TYPE release)

set(serial "1.0.0")
include_directories("../include/syukatsu")
include_directories("../include/Syukatsu/freetype2")

add_library(Syukatsu STATIC ${srcFile})

install(TARGETS Syukatsu DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/../lib)

