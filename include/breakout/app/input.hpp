#pragma once

#include "breakout/core/event_system.hpp"
#include "breakout/core/logger.hpp"


namespace brk
{
	struct InputEvent : Event {
		enum class Type : uint8_t { KeyDown, KeyUp, MouseButtonDown, MouseButtonUp, MouseMotion } type;
		int keycode = 0;
		int button = 0;
		float x = 0;
		float y = 0;

		// Default constructor
		InputEvent() : type(Type::KeyDown) {}

		// Constructor with parameters
		explicit InputEvent(Type t, int key = 0, int btn = 0, float posX = 0, float posY = 0)
			: type(t), keycode(key), button(btn), x(posX), y(posY) {}
	};


	// InputManager extending EventDispatcher for InputEvent
	class InputManager : public EventDispatcher<InputEvent> {
	public:
		void processEvent(const InputEvent& event) const
		{
			notifyListeners(event);
		}
	};

	/*
	// Example of how to use the EventListener interface
	class PlayerController final : public EventListener<InputEvent> {
	public:
		void onNotify(const InputEvent& event) override {
			switch (event.type) {
			case InputEvent::Type::KeyDown:
				BRK_LOG_INFO(brk::logger::general, "Key down: {0}", event.keycode);
				break;
			case InputEvent::Type::KeyUp:
				BRK_LOG_INFO(brk::logger::general, "Key up: {0}", event.keycode);
				break;
			case InputEvent::Type::MouseButtonDown:
				BRK_LOG_INFO(brk::logger::general, "Mouse button down at ({0}, {1})", event.x, event.y);
				break;
			case InputEvent::Type::MouseButtonUp:
				BRK_LOG_INFO(brk::logger::general, "Mouse button up at ({0}, {1})", event.x, event.y);
				break;
			case InputEvent::Type::MouseMotion:
				BRK_LOG_INFO(brk::logger::general, "Mouse moved to ({0}, {1})", event.x, event.y);
				break;
			}
		}
	};
	*/

} // namespace brk
