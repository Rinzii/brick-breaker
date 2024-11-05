#pragma once


#include <breakout/gpu/vk_types.hpp>

struct SDL_Window;

namespace brk {
    constexpr VkExtent2D default_window_size{ 1700 , 900 };

    struct  Game {
        struct Config {
            VkExtent2D startupWindowSize{ default_window_size };
            std::string_view startupWindowTitle{ "Breakout" };
            bool enableResizableWindow{ false }; // Keep this false until window resizing works
            bool enableValidationLayers{ false };
        } config{};


        bool m_isInitialized{ false };
        int m_frameNumber {0};
        bool m_stop_rendering{ false };

        static Game& Get();

        //initializes everything in the engine
        bool init();

        //shuts down the engine
        void cleanup();

        //draw loop
        void draw();

        //run the main loop
        void run();

        struct Deleter
        {
            void operator()(SDL_Window * ptr) const;
        };

        std::unique_ptr<SDL_Window, Deleter> m_window;
    };
}
