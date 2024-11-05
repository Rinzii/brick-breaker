
#pragma once
#include "breakout/app/input.hpp"

namespace brk
	{

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
	} // namespace brk
