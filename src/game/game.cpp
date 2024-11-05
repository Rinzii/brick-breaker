
#include "breakout/game/game.hpp"

#include <SDL3/SDL.h>
#include <SDL3/SDL_vulkan.h>

#include <breakout/gpu/vk_initializers.hpp>
#include <breakout/gpu/vk_types.hpp>

#include <chrono>
#include <thread>

#include "breakout/core/logger.hpp"

namespace brk {

	namespace
	{
		// TODO: Remove usage of singleton pattern.
		Game* loadedGame = nullptr; // NOLINT - Singleton pattern will always be global and can't be const.
		bk::Logger constexpr s_logger("Game");
	}

	bool Game::init(GameConfig config)
	{
		assert(loadedGame == nullptr);
		loadedGame = this;

		m_config = config;

		if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS)) {
			BK_LOG_ERROR(s_logger, "SDL_Init failed: {}", SDL_GetError());
			return false;
		}

		auto window_flags = SDL_WINDOW_VULKAN;
		SDL_Window* window = SDL_CreateWindow(
			m_config.windowConfig.startupWindowTitle.data(),
			static_cast<int>(m_config.windowConfig.startupWindowSize.width),
			static_cast<int>(m_config.windowConfig.startupWindowSize.height),
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
		while(!m_shouldGameQuit) {
			processSDLEvents();
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

	void Game::processSDLEvents()
	{
		// TODO: Abstract this to a wrapper at some point.
		SDL_Event e;
		while(SDL_PollEvent(&e)) {
			if(e.type == SDL_EVENT_QUIT) {
				m_shouldGameQuit = true;
			}

			if (e.type == SDL_EVENT_WINDOW_MINIMIZED) {
				m_stop_rendering = true;
			}

			if (e.type == SDL_EVENT_WINDOW_RESTORED) {
				m_stop_rendering = false;
			}

		}
	}

	void Game::processInput()
	{

	}


	void Game::Deleter::operator()(SDL_Window * ptr) const
	{
		SDL_DestroyWindow(ptr);
	}
} // namespace brk
