#include "Thread_Safety_Queue.hpp"

Thread_Safety_Queue::Thread_Safety_Queue(size_t size_object) :_size_object(size_object){

}

Thread_Safety_Queue::Thread_Safety_Queue(const Thread_Safety_Queue& queue) {
	std::scoped_lock guard(_mutex, queue._mutex);
	_data = queue._data;
}

Thread_Safety_Queue::Thread_Safety_Queue(Thread_Safety_Queue&& queue) noexcept{
	std::scoped_lock guard(_mutex, queue._mutex);
	_data = std::move(queue._data);
}

Thread_Safety_Queue& Thread_Safety_Queue::operator=(const Thread_Safety_Queue& queue) {
	if (this == &queue) return *this;
	std::scoped_lock guard(this->_mutex, queue._mutex);
	_data = queue._data;
	return *this;
}

Thread_Safety_Queue& Thread_Safety_Queue::operator=(Thread_Safety_Queue&& queue) noexcept {
	if (this == &queue) return *this;
	std::scoped_lock guard(_mutex, queue._mutex);
	_data = std::move(queue._data);
	return *this;
}

std::byte Thread_Safety_Queue::pop() {
	std::unique_lock<std::mutex> lock(_mutex);
	_cond.wait(lock, [this] { return !_data.empty(); });
	std::byte item = _data.front();
	_data.pop();
	return item;
}

void Thread_Safety_Queue::push(std::byte elem) {
	std::lock_guard<std::mutex> guard(_mutex);
	_data.push(elem);
	_cond.notify_one();
}

std::byte Thread_Safety_Queue::back() const {
	std::lock_guard<std::mutex> guard(_mutex);
	if (!_data.empty())
		return _data.back();
}

std::byte Thread_Safety_Queue::front() const {
	std::lock_guard<std::mutex> guard(_mutex);
	if (!_data.empty())
		return _data.front();
}

bool Thread_Safety_Queue::empty() const {
	std::lock_guard<std::mutex> guard(_mutex);
	return _data.empty();
}

size_t Thread_Safety_Queue::size() const {
	std::lock_guard<std::mutex> guard(_mutex);
	return _data.size();
}

void Thread_Safety_Queue::swap(Thread_Safety_Queue& rhs) {
	if (this == &rhs) return;
	std::scoped_lock guard(_mutex, rhs._mutex);
	std::swap(_data, rhs._data);
}