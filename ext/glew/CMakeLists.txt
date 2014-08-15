LIST(APPEND EXTRA_LIBS ${PROJECT_BINARY_DIR}glew)

add_library(glew src/glew.c)
set_target_properties(glew PROPERTIES COMPILE_DEFINITIONS "GLEW_STATIC=1")
target_include_directories(glew PUBLIC include)

