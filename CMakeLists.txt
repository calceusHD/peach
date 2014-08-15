project(peach)

cmake_minimum_required(VERSION 2.8)


add_subdirectory(ext)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libgcc -static-libstdc++ -std=c++11")
include(gl.cmake)
add_executable(Peach main.cpp ${SOURCE_FILES})
set_target_properties(Peach PROPERTIES COMPILE_DEFINITIONS "GLEW_STATIC=1")
target_include_directories(Peach PUBLIC ext/glew/include ext/glfw/include)
target_link_libraries(Peach glfw glew opengl32 gdi32)