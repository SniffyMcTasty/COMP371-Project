cmake_minimum_required (VERSION 3.8)

project(shader_viewer)

set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_CXX_STANDARD 20)

find_package(OpenGL REQUIRED COMPONENTS OpenGL)
find_package(GLEW REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)

set(ALL_LIBS
        OpenGL::GL
        OpenGL::GLU
        GLEW::GLEW
        glfw
        glm::glm
        )

add_definitions(
        -DTW_STATIC
        -DTW_NO_LIB_PRAGMA
        -DTW_NO_DIRECT3D
        -DGLEW_STATIC
        -D_CRT_SECURE_NO_WARNINGS
        -DGLM_ENABLE_EXPERIMENTAL
        -DUSE_ZLIB_T
)

aux_source_directory(src SOURCES)
add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} ${ALL_LIBS})
