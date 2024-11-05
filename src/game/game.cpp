#include "breakout/game/game.hpp"

#include <SDL3/SDL.h>
#include <SDL3/SDL_vulkan.h>

#include <breakout/gpu/vk_initializers.hpp>
#include <breakout/gpu/vk_types.hpp>

#include <chrono>
#include <thread>

#include "breakout/app/input.hpp"
#include "breakout/core/logger.hpp"
#include "breakout/game/player_controller.hpp"

namespace brk
{

	namespace
	{
		// TODO: Remove usage of singleton pattern.
		Game * loadedGame = nullptr; // NOLINT - Singleton pattern will always be global and can't be const.
		Logger const s_logger("Game");
	}

	bool Game::init(GameConfig config)
	{
		assert(loadedGame == nullptr);
		loadedGame = this;

		m_config = config;

		if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS))
		{
			BRK_LOG_ERROR(s_logger, "SDL_Init failed: {}", SDL_GetError());
			return false;
		}

		auto window_flags   = SDL_WINDOW_VULKAN;
		SDL_Window * window = SDL_CreateWindow(
			m_config.windowConfig.startupWindowTitle.data(),
			static_cast<int>(m_config.windowConfig.startupWindowSize.width),
			static_cast<int>(m_config.windowConfig.startupWindowSize.height),
			window_flags
			);

		m_window = std::unique_ptr<SDL_Window, Deleter>(window);

		m_inputDispatcher.registerListener(std::make_shared<PlayerController>());

		m_isInitialized = true;

		return true;
	}

	// ReSharper disable once CppMemberFunctionMayBeStatic
	void Game::cleanup()
	{
		// NOLINT(*-convert-member-functions-to-static)
		loadedGame = nullptr; // TODO: Using basic singleton for now. Update this later to use something better.
	}

	Game & Game::Get()
	{
		return *loadedGame;
	}

	void Game::run()
	{
		while (!m_shouldGameQuit)
		{
			processSDLEvents();
			processInput();
			if (m_stop_rendering)
			{
				// Slow down the loop if we're not rendering. No need for unnecessary CPU usage.
				std::this_thread::sleep_for(std::chrono::milliseconds(100)); // NOLINT(*-magic-numbers)
				continue;
			}

			draw();
		}

	}


	void Game::draw()
	{
		// nothing yet
	}

	void Game::processSDLEvents()
	{
		// TODO: Abstract this to a wrapper at some point.
		SDL_Event e;
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_EVENT_QUIT)
			{
				m_shouldGameQuit = true;
			}

			if (e.type == SDL_EVENT_WINDOW_MINIMIZED)
			{
				m_stop_rendering = true;
			}

			if (e.type == SDL_EVENT_WINDOW_RESTORED)
			{
				m_stop_rendering = false;
			}

		}
	}

	void Game::processInput()
	{
		// TODO: This will work for now as a basic abstraction for the input system,
		//		 but it needs to be improved further ideally to abstract all forward facing SDL events.
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_EVENT_QUIT: m_shouldGameQuit = true;
				break;

			case SDL_EVENT_KEY_DOWN: m_inputDispatcher.notifyListeners(InputEvent{InputEvent::Type::KeyDown, static_cast<int>(event.key.key)});
				break;

			case SDL_EVENT_KEY_UP: m_inputDispatcher.notifyListeners(InputEvent{InputEvent::Type::KeyUp, static_cast<int>(event.key.key)});
				break;

			case SDL_EVENT_MOUSE_BUTTON_DOWN: m_inputDispatcher.notifyListeners(
					InputEvent{InputEvent::Type::MouseButtonDown, SDLK_UNKNOWN, event.button.button, event.button.x, event.button.y});
				break;

			case SDL_EVENT_MOUSE_BUTTON_UP: m_inputDispatcher.notifyListeners(
					InputEvent{InputEvent::Type::MouseButtonUp, SDLK_UNKNOWN, event.button.button, event.button.x, event.button.y});
				break;

			case SDL_EVENT_MOUSE_MOTION: m_inputDispatcher.notifyListeners(
					InputEvent{InputEvent::Type::MouseMotion, SDLK_UNKNOWN, 0, event.motion.x, event.motion.y});
				break;
			default: break;
			}
		}
	}


	void Game::Deleter::operator()(SDL_Window * ptr) const
	{
		SDL_DestroyWindow(ptr);
	}
} // namespace brk
