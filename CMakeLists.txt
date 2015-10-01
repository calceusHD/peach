project(PEACH)

cmake_minimum_required(VERSION 2.8)


add_subdirectory(ext)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libgcc -static-libstdc++ -std=c++11")
set(SOURCE_FILES)
include(gl.cmake)
include(font.cmake)

file(COPY res DESTINATION ${PEACH_BINARY_DIR})
list(APPEND SOURCE_FILES src/Tile.cpp src/TileRenderer.cpp src/Stroke.cpp src/LineGenrator.cpp src/Vertex.cpp)
add_executable(Peach src/main.cpp ${SOURCE_FILES})
set_target_properties(Peach PROPERTIES COMPILE_DEFINITIONS "GLEW_STATIC=1 GLM_FORCE_RADIANS=1")
target_include_directories(Peach PUBLIC ext/glew/include ext/glfw/include ext/glm ext/freetype/include src)
add_custom_command(TARGET Peach POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${PROJECT_SOURCE_DIR}/res"
        ${PEACH_BINARY_DIR})
set(LIBS glfw glew freetype)
if(WIN32)
list(APPEND LIBS opengl32 gdi32)
else()
find_package(OpenGL REQUIRED)
find_package(X11 REQUIRED)

list(APPEND LIBS GL GLU X11 EGL wayland-client wayland-egl pthread xkbcommon Xxf86vm Xi Xrandr Xcursor)

endif()
target_link_libraries(Peach  ${LIBS})
