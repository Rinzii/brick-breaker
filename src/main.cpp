

#include "breakout/game/game.hpp"
#include "breakout/core/logger.hpp"

static constexpr auto logFile{"brick_break.log"};


int main(int argc, char* argv[])
{

    const auto config = brk::logger::Config{};

    // Required to initialize the logger for the application. This must also stay outside any try/catch blocks.
    auto logger = brk::logger::Instance{logFile, config};

    BRK_LOG(brk::logger::general, "Brick break game starting up!");

    brk::Game game;

    game.init();

    game.run();

    game.cleanup();
    //glfwCreateWindow

    return 0;
}


/*
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>
#include <imgui.h>
#include <memory>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "breakout/core/logger.hpp"

static constexpr auto logFile{"brick_break.log"};

void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

int main() {
    const auto config = bk::logger::Config{};

    // Required to initialize the logger for the application. This must also stay outside any try/catch blocks.
    auto logger = bk::logger::Instance{logFile, config};

    BK_LOG(bk::logger::general, "Brick break game starting up!");

    // Initialize GLFW
    glfwInit();

    // check for vulkan support
    if (GLFW_FALSE == glfwVulkanSupported()) {
        BK_LOG_ERROR(bk::logger::general, "Vulkan not supported on this system.");
        glfwTerminate();
        return EXIT_FAILURE;
    }

    // create a window
    int width = 800;
    int height = 600;
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API); // This tells GLFW to not create an OpenGL context with the window
    const auto window = glfwCreateWindow(width, height, "Breakout", nullptr, nullptr);
    if (window == nullptr) {
        BK_LOG_ERROR(bk::logger::general, "Failed to create GLFW window");
        glfwTerminate();
        return EXIT_FAILURE;
    }


    // make sure we indeed get the surface size we want.
    glfwGetFramebufferSize(window, &width, &height);

    // render loop
    while (!glfwWindowShouldClose(window)) {
        // input
        processInput(window);

        // render here

        glfwPollEvents();
    }

    // destroy the window using GLFW function
    glfwDestroyWindow(window);

    // remember to terminate glfw
    glfwTerminate();
    BK_LOG(bk::logger::general, "Brick break game shutting down. Goodbye!");

    return EXIT_SUCCESS;
}
*/
