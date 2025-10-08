#include <algorithm>
#include <concepts>
#include <tuple>
#include <typeinfo>
#include <vector>
#include <stdexcept> 
#include <type_traits>

template<typename Data>
concept Valid_Data_ = requires(Data data, Data tmp_data) {
	requires std::destructible<Data>
	&& std::movable<Data>
	&& std::copy_constructible<Data>
	&& std::move_constructible<Data>;
};

template<typename... Data>
concept Valid_Data = (Valid_Data_ <Data> && ...);

template<Valid_Data... Args>
class MyVariant final{

public:

	MyVariant() = default;
	template<Valid_Data Data> MyVariant(Data data);
	~MyVariant();

public:
	MyVariant(const MyVariant& variant);
	MyVariant& operator= (const MyVariant& variant);

public:
	MyVariant(MyVariant&& variant);
	MyVariant& operator= ( MyVariant&& variant);

public:
	template<Valid_Data_ Data>
	constexpr Data get();
	constexpr bool hold_alternative();
	constexpr size_t index() const noexcept;

private:
	template<Valid_Data_ Data>
	void construct(Data&& value);
	template<Valid_Data_ Data>
	bool find();
private:
	static constexpr size_t size = sizeof...(Args);
	static constexpr size_t max_size_ = std::max({ sizeof(Args)... });
	static constexpr size_t max_align_ = std::max({ alignof(Args)... });
	std::aligned_storage_t<max_size_, max_align_> data_;
	std::vector<const std::type_info*> info_list_ = {};
	size_t index_ = 0;
};

template <Valid_Data... Args>
template<Valid_Data Data>
MyVariant<Args...>::MyVariant(Data data) : MyVariant<Args...>() {
	(info_list_.push_back(&typeid(Args)), ...);
	construct<Data>(std::move(data));
}

template <Valid_Data... Args>
MyVariant<Args...>::~MyVariant() {

}

template <Valid_Data... Args>
MyVariant<Args...>::MyVariant(const MyVariant <Args...>& variant) {
	info_list_ = variant.info_list_;
	index_ = variant.index_;
	data_ = variant.data_;
}

template <Valid_Data... Args>
MyVariant<Args...>& MyVariant<Args...>::operator= (const MyVariant <Args...>& variant) {
	if (&variant != this) {
		info_list_ = variant.info_list_;
		index_ = variant.index_;
		data_ = variant.data_;
	}	
	return *this;
}

template <Valid_Data... Args>
MyVariant<Args...>::MyVariant(MyVariant <Args...>&& variant) {
	info_list_ = variant.info_list_;
	data_ = variant.data_;
	index_ = variant.index_;
}

template <Valid_Data... Args>
MyVariant<Args...>& MyVariant<Args...>::operator= (MyVariant <Args...>&& variant) {
	if (&variant != this) {
		std::swap(info_list_, variant.info_list_);
		std::swap(data_, variant.data_);
		std::swap(index_, variant.index_);
	}
	return *this;
}

template <Valid_Data... Args>
template<Valid_Data_ Data>
constexpr Data MyVariant<Args...>::get() {
	if (info_list_[index_ - 1] != &typeid(Data)) 
		throw std::bad_variant_access();
	if (!find<Data>())
		throw std::bad_variant_access();
	return *reinterpret_cast<Data*>(&data_);
}

template <Valid_Data... Args>
constexpr bool MyVariant<Args...>::hold_alternative() {
	return info_list_.size() > 1;
}

template <Valid_Data... Args>
constexpr size_t MyVariant<Args...>::index() const noexcept {
	return index_;
}

template <Valid_Data... Args>
template<Valid_Data_ Data>
void MyVariant<Args...>::construct(Data&& value) {
	new (&data_) Data(value);
	auto tmp_index = std::find(info_list_.begin(), info_list_.end(), &typeid(Data));
	if (tmp_index != info_list_.end()) {
		index_ = std::distance(info_list_.begin(), tmp_index) + 1;
	}
	else {
		throw std::invalid_argument("Non valid value");
	}
}

template <Valid_Data... Args>
template<Valid_Data_ Data>
bool MyVariant<Args...>::find() {
	auto tmp_index = std::find(info_list_.begin(), info_list_.end(), &typeid(Data));
	if (tmp_index != info_list_.end()) {
		index_ = std::distance(info_list_.begin(), tmp_index) + 1;
		return true;
	}
	else {
		throw std::invalid_argument("Non valid value");
	}
}