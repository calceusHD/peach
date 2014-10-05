project(PEACH)

cmake_minimum_required(VERSION 2.8)


add_subdirectory(ext)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libgcc -static-libstdc++ -std=c++11")
set(SOURCE_FILES)
include(gl.cmake)
include(font.cmake)
file(COPY res DESTINATION ${PEACH_BINARY_DIR})
add_executable(Peach main.cpp ${SOURCE_FILES})
set_target_properties(Peach PROPERTIES COMPILE_DEFINITIONS "GLEW_STATIC=1")
target_include_directories(Peach PUBLIC ext/glew/include ext/glfw/include ext/glm ext/freetype/include .)
set(LIBS glfw glew freetype)
if(WIN32)
list(APPEND LIBS opengl32 gdi32)
else()
list(APPEND LIBS GL GLU X11 Xi Xcursor Xxf86vm pthread Xrandr)

endif()
target_link_libraries(Peach ${LIBS})