project(${GLOBAL_PROJ_NAME}-ext)

file(ARCHIVE_EXTRACT INPUT "${CMAKE_CURRENT_SOURCE_DIR}/src.zip" DESTINATION "${CMAKE_CURRENT_SOURCE_DIR}")

# imgui (zip file) - TODO: Planning to move this to a git fork
add_subdirectory(src/imgui)
add_library(imgui::imgui ALIAS imgui)

# stb (zip file)
add_subdirectory(src/stb)
add_library(stb::image ALIAS stb-image)

# Vulkan
find_package(Vulkan 1.3.296 REQUIRED)

# VkBootstrap
CPMAddPackage(
        NAME vk-bootstrap
        GITHUB_REPOSITORY charles-lunarg/vk-bootstrap
        GIT_TAG v1.3.296
)

# tinyobjloader
CPMAddPackage(
        NAME tinyobjloader
        GITHUB_REPOSITORY tinyobjloader/tinyobjloader
        GIT_TAG release
)
add_library(tiny::objloader ALIAS tinyobjloader)

# Vulkan Memory Allocator (VMA)
CPMAddPackage("gh:GPUOpen-LibrariesAndSDKs/VulkanMemoryAllocator@3.1.0")
add_library(vma::vma ALIAS VulkanMemoryAllocator)

# fmt
CPMAddPackage(
        NAME fmt
        GITHUB_REPOSITORY fmtlib/fmt
        GIT_TAG 11.0.2
)

# fastgltf
CPMAddPackage(
        NAME fastgltf
        GITHUB_REPOSITORY spnda/fastgltf
        GIT_TAG v0.8.0
)

CPMAddPackage(
        NAME WinLite
        GITHUB_REPOSITORY Rinzii/WinLite
        GIT_TAG main
)
add_library(Win::Lite ALIAS WinLite)

#CPMAddPackage("gh:Rinzii/vk-dynamic@1.3.290")

# GLFW
CPMAddPackage(
        NAME glfw
        GITHUB_REPOSITORY glfw/glfw
        GIT_TAG 3.4
        OPTIONS
        "GLFW_INSTALL OFF"
        "GLFW_BUILD_DOCS OFF"
        "GLFW_BUILD_EXAMPLES OFF"
        "GLFW_BUILD_TESTS OFF"
)
add_library(glfw::glfw ALIAS glfw)

# SDL3
CPMAddPackage(
        NAME sdl3
        GITHUB_REPOSITORY libsdl-org/SDL
        GIT_TAG preview-3.1.6
)

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

target_link_libraries(${PROJECT_NAME} INTERFACE
        imgui::imgui
        stb::image

        Win::Lite
        glm::glm
        vma::vma
        Vulkan::Vulkan
        fmt::fmt
        tiny::objloader

        fastgltf::fastgltf

        vk-bootstrap::vk-bootstrap

        SDL3::SDL3
)

target_compile_definitions(glm INTERFACE
        GLM_FORCE_XYZW_ONLY
        GLM_FORCE_RADIANS
        GLM_FORCE_DEPTH_ZERO_TO_ONE
        GLM_FORCE_SILENT_WARNINGS
        GLM_ENABLE_EXPERIMENTAL
        GLM_EXT_INCLUDED
)
