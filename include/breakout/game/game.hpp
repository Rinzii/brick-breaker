#pragma once


#include <breakout/gpu/vk_types.hpp>
#include <breakout/app/input.hpp>

struct SDL_Window;

namespace brk
{
	constexpr VkExtent2D default_window_size{1700, 900};

	struct Game
	{
		struct WindowConfig
		{
			VkExtent2D startupWindowSize{default_window_size};
			std::string_view startupWindowTitle{"Breakout"};
			bool enableResizableWindow{false}; // Keep this false until window resizing works

			WindowConfig() = default;
		};

		struct GpuConfig
		{
			bool enableValidationLayers{false};

			GpuConfig() = default;
		};

		struct GameConfig
		{
			WindowConfig windowConfig;
			GpuConfig gpuConfig;

			GameConfig() : windowConfig{}, gpuConfig{} {}
		};

		static Game & Get();

		//initializes everything in the engine
		bool init(GameConfig config = GameConfig());

		//shuts down the engine
		void cleanup();

		//draw loop
		void draw();

		//run the main loop
		void run();

	private:
		void processSDLEvents();
		void processInput();

		GameConfig m_config;

		bool m_shouldGameQuit{false};
		bool m_isInitialized{false};
		int m_frameNumber{0};
		bool m_stop_rendering{false};

		struct Deleter
		{
			void operator()(SDL_Window * ptr) const;
		};

		std::unique_ptr<SDL_Window, Deleter> m_window;

		InputManager m_inputDispatcher;

	};
}
