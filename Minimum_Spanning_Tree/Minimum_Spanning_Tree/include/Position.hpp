#pragma once
#include <iostream>
#include <string>
#include <concepts>
#include <utility>
#include <type_traits>

//template<typename T, typename U>
//concept Is_integral_str = std::is_integral<T> || std::is_same<std::string,T> && std::is_integral<U> || std::is_floating_point<U>;

//template<typename T>
//concept Is_integral_fl = std::is_integral<T> || std::is_floating_point<T>;

template <typename one = int, typename two = int>
class Position final {
private:
	std::pair<one, two> pos{};

public:
	Position() = default;
	Position(const one& x,const two& y);
	explicit Position(std::pair<one, two> &position);
	Position(const Position& position);
	~Position();

public:
	Position& operator = (const Position& position);
	bool operator < (const Position& position) const;

public:
	one first_vertex();
	two second_vertex();
};

template <typename one, typename two>
Position<one, two>::Position(const one& x, const two& y) : Position() {
	pos.first = x;
	pos.second = y;
}

template <typename one, typename two>
Position<one, two>::~Position(){

}

template <typename one, typename two>
Position<one, two>::Position(std::pair<one, two>& position) : Position() {
	pos.first = position.first;
	pos.second = position.second;
}

template <typename one, typename two>
Position<one, two>::Position(const Position& position) :Position() {
	pos = position.pos;
}

template <typename one, typename two>
Position<one, two>& Position<one, two>::operator =(const Position& position) {
	if (this != &position) {
		pos = position.pos;
	}
	return *this;
}
template <typename one, typename two>
bool Position<one, two>::operator < (const Position& position) const {
	return position.pos.second < pos.second;
}

template <typename one, typename two>
one Position<one, two>::first_vertex() {
	return pos.first;
}

template <typename one, typename two>
two Position<one, two>::second_vertex() {
	return pos.second;
}
