#要求するcmakeのバージョン
cmake_minimum_required(VERSION 2.8)

set(Project GameTest)
#project name
PROJECT(${Project})

set(srcFile GLFWGameTest.cpp TestListsScene.cpp Camera2DTestScene.cpp Camera3DTestScene.cpp SpriteBatcherTestScene.cpp SimpleObjectFactory.cpp)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 ")

# find packages
find_package(OPENGL)
find_package(GLUT)
find_package(GLEW)
find_package(GLFW)

#include_directories(/usr/local/include)
include_directories(~/freeglut-2.8.1/include)
include_directories(${GLEW_INCLUDE_DIR})
include_directories(${GLFW_INCLUDE_DIR})

#link_directories(~/glew-1.10.0/lib)
#link_directories(${GLEW_LIBRARY})
link_directories(../bin)
set(CMAKE_BUILD_TYPE release)

#add_executable(${Project} )
add_executable(${Project} ${srcFile})
target_link_libraries(${Project} /System/Library/Frameworks/GLUT.framework ${OPENGL_LIBRARY} m)
target_link_libraries(${Project} GLEW.a)
target_link_libraries(${Project} libGLFWGame.a)
target_link_libraries(${Project} ${GLFW_LIBRARY})


