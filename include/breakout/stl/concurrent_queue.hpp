#pragma once

#include <queue>
#include <mutex>
#include <condition_variable>
#include <optional>

namespace brk
{
	template <typename T, typename Container = std::deque<T>>
	class concurrent_queue
	{
	public:
		using container_type = Container;
		using value_type = typename Container::value_type;
		using size_type = typename Container::size_type;
		using reference = typename Container::reference;
		using const_reference = typename Container::const_reference;

	private:
		Container m_container;
		std::mutex m_mutex;
		std::condition_variable m_cond;

	public:
		concurrent_queue() = default;

		concurrent_queue(const concurrent_queue&) = delete;
		concurrent_queue& operator=(const concurrent_queue&) = delete;

		concurrent_queue(concurrent_queue&&) = delete;
		concurrent_queue& operator=(concurrent_queue&&) = delete;

		~concurrent_queue() = default;

		void push(const T& item)
		{
			{
				std::lock_guard lock(m_mutex);
				m_container.push_back(item);
			}
			m_cond.notify_one();
		}

		void push(T&& item)
		{
			{
				std::lock_guard lock(m_mutex);
				m_container.push_back(std::move(item));
			}
			m_cond.notify_one();
		}

		void emplace(auto&&... args)
		{
			{
				std::lock_guard lock(m_mutex);
				m_container.emplace_back(std::forward<decltype(args)>(args)...);
			}
			m_cond.notify_one();
		}

		T pop()
		{
			std::unique_lock lock(m_mutex);
			m_cond.wait(lock, [this]() { return !m_container.empty(); });

			T item = std::move(m_container.front());
			m_container.pop_front();
			return item;
		}

		std::optional<T> try_pop()
		{
			std::lock_guard lock(m_mutex);
			if (m_container.empty())
			{
				return std::nullopt;
			}

			T item = std::move(m_container.front());
			m_container.pop_front();
			return item;
		}
	}; // class concurrent_queue
} // namespace brk
