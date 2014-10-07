add_subdirectory(glew)
add_subdirectory(freetype)
set(GLM_FORCE_RADIANS ON CACHE BOOL "sdfglsd")

add_subdirectory(glfw)
set(GLFW_BUILD_EXAMPLES OFF FORCE BOOL "Build the GLFW example programs")
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "Build the GLFW example programs")
set(GLFW_BUILD_TESTS OFF FORCE  BOOL "a")
set(GLFW_BUILD_TESTS OFF CACHE  BOOL "a")
