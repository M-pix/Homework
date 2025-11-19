#include "FIFO.hpp"
#include <algorithm>

void Multithreading_Buffer::_input(std::byte data, Thread_Safety_Queue buffer) {
	buffer.push(data);
}

std::byte Multithreading_Buffer::output(Thread_Safety_Queue buffer, size_t length) {
	return buffer.pop();
}

void Multithreading_Buffer::input(std::initializer_list<std::byte> data, Thread_Safety_Queue buffer) {
	std::for_each(data.begin(), data.end(), [&buffer](std::byte elem) {_input(elem, buffer); });
}