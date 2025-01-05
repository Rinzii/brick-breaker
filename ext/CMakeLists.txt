project(${GLOBAL_PROJ_NAME}-ext)

# fmt
CPMAddPackage(
        NAME fmt
        GITHUB_REPOSITORY fmtlib/fmt
        GIT_TAG 11.0.2
)

# GLFW
CPMAddPackage(
        NAME glfw
        GITHUB_REPOSITORY glfw/glfw
        GIT_TAG 3.4
        OPTIONS
        "GLFW_INSTALL ON"
        "GLFW_BUILD_DOCS OFF"
        "GLFW_BUILD_EXAMPLES OFF"
        "GLFW_BUILD_TESTS OFF"
)
add_library(glfw::glfw ALIAS glfw)


# sfml
CPMAddPackage(
        NAME sfml
        GITHUB_REPOSITORY SFML/SFML
        GIT_TAG 3.0.0
)

CPMAddPackage(
        NAME WinLite
        GITHUB_REPOSITORY Rinzii/WinLite
        GIT_TAG main
)
add_library(Win::Lite ALIAS WinLite)

# GLM
CPMAddPackage(
        NAME glm
        GITHUB_REPOSITORY g-truc/glm
        GIT_TAG 1.0.1
        OPTIONS
        "GLM_ENABLE_CXX_20 ON"
)

if(CMAKE_CXX_COMPILER_ID STREQUAL GNU)
    target_compile_options(glm INTERFACE -Wno-volatile)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL Clang)
    target_compile_options(glm INTERFACE -Wno-deprecated-volatile)
endif()

add_library(${PROJECT_NAME} INTERFACE)
add_library(${GLOBAL_PROJ_NAME}::ext ALIAS ${PROJECT_NAME})

# TODO: Add imgui-sfml

target_link_libraries(${PROJECT_NAME} INTERFACE

        Win::Lite
        glm::glm
        fmt::fmt
        SFML::Graphics
        SFML::Audio

)

target_compile_definitions(glm INTERFACE
        GLM_FORCE_XYZW_ONLY
        GLM_FORCE_RADIANS
        GLM_FORCE_DEPTH_ZERO_TO_ONE
        GLM_FORCE_SILENT_WARNINGS
        GLM_ENABLE_EXPERIMENTAL
        GLM_EXT_INCLUDED
)
