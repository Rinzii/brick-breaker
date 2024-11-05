#pragma once

#include <vector>
#include <memory>
#include <algorithm>

namespace brk
{
	// Event Base Struct
	struct Event {
		virtual ~Event() = default;
		Event(const Event&) = delete;
		Event& operator=(const Event&) = delete;
		Event(Event&&) = delete;
		Event& operator=(Event&&) = delete;

	protected:
		Event() = default; // Only derived classes can be instantiated
	};

	// EventListener Interface
	template <typename EventType>
	class EventListener {
	public:
		EventListener() = default;
		virtual ~EventListener() = default;
		EventListener(const EventListener&) = delete;
		EventListener& operator=(const EventListener&) = delete;
		EventListener(EventListener&&) = delete;
		EventListener& operator=(EventListener&&) = delete;

		virtual void onNotify(const EventType& event) = 0;
	};

	// EventDispatcher Class Template
	template <typename EventType>
	class EventDispatcher {
	public:
		using ListenerPtr = std::shared_ptr<EventListener<EventType>>;

		// Register a listener
		void registerListener(ListenerPtr listener) {
			listeners.push_back(listener);
		}

		// Unregister a listener
		void removeListener(ListenerPtr listener) {
			listeners.erase(std::remove(listeners.begin(), listeners.end(), listener), listeners.end());
		}

		// Notify all listeners of an event
		void notifyListeners(const EventType& event) const {
			for (const auto& listener : listeners) {
				if (listener) {
					listener->onNotify(event);
				}
			}
		}

	private:
		std::vector<ListenerPtr> listeners;
	};
}
