#pragma once
#include <math.h>
#include <concepts>
#include <algorithm>

template<typename T>
struct isPair : std::false_type {};

template<typename T1, typename T2>
struct isPair<std::pair<T1, T2>> : std::true_type {};

template<typename Data>
concept MutableIterable = requires(Data c) {
	{ *std::begin(c) } -> std::same_as<typename Data::reference>;
	requires std::is_assignable_v<typename Data::reference, double>;
};

template <typename Data>
concept Container = requires(Data a) {
	{ std::begin(a) } -> std::input_iterator;
	{ std::end(a) } -> std::sentinel_for<decltype(std::begin(a))>;
	std::is_arithmetic<Data> ::value;}
	&& !isPair<std::remove_cvref_t<decltype(*std::begin(std::declval<Data>()))>>::value
	&& (MutableIterable<Data>) ;

template <typename Data>
concept ContainerConst = requires(Data a) {
	{ std::begin(a) } -> std::input_iterator;
	{ std::end(a) } -> std::sentinel_for<decltype(std::begin(a))>;
	std::default_initializable<Data>;
	std::copyable<Data>;
	std::is_arithmetic<Data> ::value;}
	&& !isPair<std::remove_cvref_t<decltype(*std::begin(std::declval<Data>()))>>::value
	&& (!MutableIterable<Data>);

template <typename Data>
concept ContainerKeyValue = requires(Data a) {
	{ std::begin(a) } -> std::input_iterator;
	{ std::end(a) } -> std::sentinel_for<decltype(std::begin(a))>;
	std::is_arithmetic<typename Data::value_type> ::value;}
	&& isPair<std::remove_cvref_t<decltype(*std::begin(std::declval<Data>()))>>::value;

template <typename Data>
concept standart = requires(Data a) { 
	std::is_arithmetic<Data> ::value; 

} && !Container<Data> && !ContainerKeyValue<Data> && !ContainerConst<Data>;

// deque проверка на стандартный тип , контейнер копирования для стандарт

template<standart Data>
void ultimateSQRT(Data& data) {
	data = std::sqrt(data);
}

template<Container Data>
void ultimateSQRT (Data& data) {
	std::ranges::for_each(data, [](auto& elem){elem = std::sqrt(elem);});
	//for (auto& elem : data) {
	//	elem = std::sqrt(elem);
	//}
}

template<ContainerConst Data>
void ultimateSQRT(Data& data) {
	using ContainerType = std::remove_reference_t<Data>;
	ContainerType tmp;
	for (auto elem : data) {
		tmp.insert(std::sqrt(elem));
	}
	data = tmp;
}

template<ContainerKeyValue Data>
void ultimateSQRT(Data& data) {
	for (auto&[_, value] : data) { // если не по ссылке то не будет присваиваться а будет просто в стеке временное значение считать
		value = std::sqrt(value);
	}
}