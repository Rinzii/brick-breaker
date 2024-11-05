
#include "breakout/game/game.hpp"

#include <SDL3/SDL.h>
#include <SDL3/SDL_vulkan.h>

#include <breakout/gpu/vk_initializers.hpp>
#include <breakout/gpu/vk_types.hpp>

#include <chrono>
#include <thread>

#include "breakout/core/logger.hpp"

namespace brk {

	Game* loadedGame = nullptr;

	bool Game::init() {
		assert(loadedGame == nullptr);
		loadedGame = this;

		SDL_Init(SDL_INIT_VIDEO);

		auto window_flags = SDL_WINDOW_VULKAN;
		SDL_Window* window = SDL_CreateWindow(
			config.startupWindowTitle.data(),
			static_cast<int>(config.startupWindowSize.width),
			static_cast<int>(config.startupWindowSize.height),
			window_flags
			);

		m_window = std::unique_ptr<SDL_Window, Deleter>(window);

		m_isInitialized = true;

		return true;
	}

	// ReSharper disable once CppMemberFunctionMayBeStatic
	void Game::cleanup() { // NOLINT(*-convert-member-functions-to-static)
		loadedGame = nullptr; // TODO: Using basic singleton for now. Update this later to use something better.
	}

	Game & Game::Get() {
		return *loadedGame;
	}

	void Game::run() {
		bool ready_to_quit = false;
		SDL_Event e;
		while(!ready_to_quit) {
			while(SDL_PollEvent(&e)) {
				if(e.type == SDL_EVENT_QUIT) {
					ready_to_quit = true;
				}

				if (e.type == SDL_EVENT_WINDOW_MINIMIZED) {
					m_stop_rendering = true;
				}

				if (e.type == SDL_EVENT_WINDOW_RESTORED) {
					m_stop_rendering = false;
				}

			}
			if (m_stop_rendering) {
				// Slow down the loop if we're not rendering. No need for unnecessary CPU usage.
				std::this_thread::sleep_for(std::chrono::milliseconds(100)); // NOLINT(*-magic-numbers)
				continue;
			}

			draw();
		}


	}



	void Game::draw() {
		// nothing yet
	}


	void Game::Deleter::operator()(SDL_Window * ptr) const
	{
		SDL_DestroyWindow(ptr);
	}
} // namespace brk
