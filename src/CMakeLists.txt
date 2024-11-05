brk_add_sources(
        ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/camera.cpp
)

add_subdirectory(app)
add_subdirectory(core)
add_subdirectory(game)
add_subdirectory(gpu)
