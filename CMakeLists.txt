cmake_minimum_required(VERSION 3.18)
set(GLOBAL_PROJ_NAME breakout)
project(${GLOBAL_PROJ_NAME})

# CMake Package Manager
include(cmake/CPM.cmake)
include(cmake/config/GlobalConfig.cmake)

set(CMAKE_CXX_STANDARD 20)
add_subdirectory(ext)

include(cmake/func/AddTargetSource.cmake)
add_executable(${PROJECT_NAME})
add_subdirectory(include/breakout)
add_subdirectory(src)

# TODO: Setup a better cmake structure for adding source files
#target_sources(${PROJECT_NAME}
#        PUBLIC
#        ${breakout_headers}
#
#        PRIVATE
#        ${breakout_sources}
#)


if (CMAKE_CXX_COMPILER_ID STREQUAL MSVC OR CMAKE_CXX_COMPILER_ID STREQUAL Clang)
    # Make MSVC shut up about not actually deprecated functions
    add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
endif ()

# COMPILER FLAGS
if(CMAKE_CXX_COMPILER_ID STREQUAL Clang OR CMAKE_CXX_COMPILER_ID STREQUAL GNU)
    target_compile_options(${PROJECT_NAME} PRIVATE
            -Wall -Wextra -Wpedantic -Wconversion -Werror=return-type
    )

    if(GAME_ARCH_X64)
        target_compile_options(${PROJECT_NAME} PRIVATE
                -march=x86-64-v3
        )
    elseif (GAME_ARCH_X86 || GAME_ARCH_ARM || GAME_ARCH_ARM64)
        target_compile_options(${PROJECT_NAME} PRIVATE
                -march=native
        )
    endif()
elseif (CMAKE_CXX_COMPILER_ID STREQUAL MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE
            /W4 /WX
    )

    if(GAME_ARCH_X64)
        target_compile_options(${PROJECT_NAME} PRIVATE
                /arch:AVX2
        )
    elseif (GAME_ARCH_X86)
        target_compile_options(${PROJECT_NAME} PRIVATE
                /arch:SSE2
        )
    elseif (GAME_ARCH_ARM)
        target_compile_options(${PROJECT_NAME} PRIVATE
                /arch:ARMv7VE
        )
    elseif (GAME_ARCH_ARM64)
        target_compile_options(${PROJECT_NAME} PRIVATE
                /arch:armv8.0
        )
    endif()
endif()

target_link_libraries(${PROJECT_NAME}
        PRIVATE
        ${PROJECT_NAME}::ext
)

# Setup our include structure
target_include_directories(${PROJECT_NAME}
        PUBLIC include "${CMAKE_CURRENT_BINARY_DIR}/include"
        PRIVATE "src"
)
