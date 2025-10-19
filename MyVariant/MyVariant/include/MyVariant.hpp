#include <algorithm>
#include <concepts>
#include <stdexcept> 
#include <type_traits>
#include "FindIndex.hpp"



template<Valid_Data... Args>
class MyVariant final{
public:
	MyVariant() = default;
	template<Valid_Data Data> 
	constexpr MyVariant(Data&& data) noexcept;
	constexpr MyVariant(const MyVariant& variant)  noexcept;
	constexpr MyVariant(MyVariant&& variant)  noexcept;
	constexpr MyVariant& operator= (const MyVariant& variant);
	constexpr MyVariant& operator= (MyVariant&& variant);

public:
	template< Valid_Data_ Data>
	constexpr Data myget();
	template<size_t index>
	constexpr decltype (auto) myget();
	template <Valid_Data_ Finder>
	constexpr bool hold_alternative();
	constexpr size_t index() const noexcept;

private:
	static constexpr size_t size_ = sizeof...(Args);
	static constexpr size_t max_size_ = std::max({sizeof(Args)...});
	static constexpr size_t max_align_ = std::max({alignof(Args)...});
	std::aligned_storage_t<max_size_, max_align_> data_;
	size_t index_ = 0;
};

template <Valid_Data... Args>
template<Valid_Data Data>
constexpr MyVariant<Args...>::MyVariant(Data&& data) noexcept {
	new (&data_) Data(std::forward<Data>(data));
	index_ = Index<Data, Args...>::value;
}

template <Valid_Data... Args>
constexpr MyVariant<Args...>::MyVariant(const MyVariant <Args...>& variant) noexcept{
	index_ = variant.index_;
	size_t index = 0;
	((index++ == index_ ? new (data_) Args(*reinterpret_cast<Args*>(variant.data_)) : void()), ...);
}

template <Valid_Data... Args>
constexpr MyVariant<Args...>& MyVariant<Args...>::operator= (const MyVariant <Args...>& variant) {
	if (&variant != this) {
		index_ = variant.index_;
		size_t index = 0;
		((index++ == index_ ? new (data_) Args(*reinterpret_cast<Args*>(variant.data_)) : void()), ...);
	}	
	return *this;
}

template <Valid_Data... Args>
constexpr MyVariant<Args...>::MyVariant(MyVariant <Args...>&& variant) 	noexcept{
	std::swap(data_, variant.data_);
	std::swap(index_, variant.index_);
}

template <Valid_Data... Args>
constexpr MyVariant<Args...>& MyVariant<Args...>::operator= (MyVariant <Args...>&& variant) {
	if (&variant != this) {
		std::swap(data_, variant.data_);
		std::swap(index_, variant.index_);
	}
	return *this;
}

template<Valid_Data... Args>
template<Valid_Data_ Data>
constexpr Data MyVariant<Args...>::myget() {
	using type = ValueType<Data, Args...>::Type;
	static_assert(std::is_same<type,Data>::value,"Non valid type");
	return *reinterpret_cast<Data*>(&data_);
}

template<Valid_Data... Args>
template<size_t index>
constexpr decltype (auto) MyVariant<Args...>::myget() {
	using type = ValueIndex<index, Args...>::Type;
	return *reinterpret_cast<type*>(&data_);
}

template < Valid_Data... Args>
template<Valid_Data_ Finder>
constexpr bool MyVariant<Args...>::hold_alternative() {
	constexpr size_t res = Index<Finder, Args...>::value;
	return res == -1 ? false : true;
}

template <Valid_Data... Args>
constexpr size_t MyVariant<Args...>::index() const noexcept {
	return index_;
}
