
#include "Thread_Safety_Queue.hpp"
#include <cstddef>


class Multithreading_Buffer {
public:
	Multithreading_Buffer() = delete;
public:
	static void _input(std::byte data, Thread_Safety_Queue buffer);
	static std::byte output(Thread_Safety_Queue buffer, size_t length);
	static void input(std::initializer_list<std::byte> data, Thread_Safety_Queue buffer);	
};
