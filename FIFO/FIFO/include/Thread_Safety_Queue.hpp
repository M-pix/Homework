#include <queue>
#include <mutex>
#include <cstddef>
#include <condition_variable>

class Thread_Safety_Queue {
public:
	Thread_Safety_Queue() = default;
	explicit Thread_Safety_Queue(size_t size_object);
	Thread_Safety_Queue(const Thread_Safety_Queue& queue);
	Thread_Safety_Queue(Thread_Safety_Queue&& queue) noexcept;
	Thread_Safety_Queue& operator=(const Thread_Safety_Queue& queue);
	Thread_Safety_Queue& operator=(Thread_Safety_Queue&& queue) noexcept;

public:
	std::byte pop();
	void push(std::byte elem);
	std::byte front() const;
	std::byte back() const;
	size_t size() const;
	bool empty() const;
	void swap(Thread_Safety_Queue &rhs);

private:
	mutable std::mutex _mutex;
	std::queue<std::byte> _data = {};
	std::condition_variable _cond;
	size_t _size_object = 0;
};
