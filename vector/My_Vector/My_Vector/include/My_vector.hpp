#pragma once
#include <utility>
#include <variant>
#include <math.h>
//template<typename T>
//concept Is_integral_str = std::is_integral_v<T>;
namespace help {
	template<typename T>
	void swap(T& arr_1, T& arr_2) {
		T tmp = std::move(arr_1);
		arr_1 = std::move(arr_2);
		arr_2 = std::move(tmp);
	}
}


template<typename T>
class My_vector final {
	//static_assert((Is_integral_str<Args> && ...));
private:
	size_t size{ 0 };
	size_t col_elem{ 0 };
	T* arr = nullptr;
	
public:
	My_vector() = default;
	My_vector(size_t size_1);
	My_vector(size_t size, T data);
	template <typename ...Args> My_vector(Args... args);
	My_vector(const My_vector& vector);
	My_vector(My_vector&& vector);
	~My_vector();

public:
	My_vector& operator = (const My_vector& vector);
	My_vector& operator = (My_vector&& vector);

public:
	void push_back(T elem);
	void swap(My_vector& vector);

private:
	void copy(const My_vector& vector);
	void move(My_vector&& vector);
};

template <typename T>
void My_vector<T>::copy(const My_vector& vector) {
	T* tmp = new T[size];
	if (tmp == nullptr)
		throw std::runtime_error("Allocation error");
	try {
		std::memcpy(tmp, arr, sizeof(T) * col_elem);
		size_t tmp_col = col_elem;
		size_t tmp_size = size;
	}
	catch (...) {
		delete[] tmp;
		throw;
	}
	size = vector.size;
	col_elem = vector.col_elem;
	delete[] arr;
	if (size > 0) {
		arr = new T[size];
		if (arr == nullptr)
			throw std::runtime_error("Allocation error");
		if (col_elem > 0) {
			std::memcpy(arr, vector.arr, sizeof(T) * col_elem);
		}	
	}
}

template <typename T>
void My_vector<T>::move(My_vector&& vector) {
	if (vector.size != 0) {
		size = vector.size;
		arr = vector.arr;
		col_elem = vector.col_elem;
		vector.arr = nullptr;
		vector.size = 0;
		vector.col_elem = 0;
	}
}

template <typename T>
My_vector<T>:: My_vector(size_t size) : My_vector(){
	size = size;
	arr = new T[size];
	if (arr == nullptr)
		throw std::runtime_error("Allocation error");
}

template <typename T>
My_vector<T>::My_vector(size_t size, T data) : My_vector() {
	size = size;
	col_elem = size;
	arr = new T[size];
	if (arr == nullptr)
		throw std::runtime_error("Allocation error");
	for (int i = 0; i < col_elem; ++i)
		arr[i] = data;
	
}

template <typename T>
template <typename ...Args>
My_vector<T>::My_vector(Args ...args) : My_vector() {
	(push_back(args), ...);
}

template <typename T>
My_vector<T>::My_vector(const My_vector& vector)  {
	copy(vector);
}

template <typename T>
My_vector<T>::My_vector(My_vector&& vector)  {
	move(vector);
}

template <typename T>
My_vector<T>::~My_vector() {
	if (arr!=nullptr)
		delete[]arr;
}

template <typename T>
My_vector<T>& My_vector<T>::operator =(const My_vector& vector) {
	if (this != &vector) {
		copy(vector);
	}
	return *this;
}

template <typename T>
My_vector<T>& My_vector<T>::operator =(My_vector&& vector) {
	if (this != &vector) {
		move(vector);
	}
	return *this;
}

template<typename T>
void My_vector<T>::push_back(T elem) {
	if (size <= col_elem) {
		if (arr != nullptr) {
			size = static_cast<size_t>(size + log2(size + 2));
			T* tmp = new T[size];
			if (tmp == nullptr)
				throw std::runtime_error("Allocation error");
			std::memcpy(tmp, arr, sizeof(T) * col_elem);
			//delete [] arr;
			arr = tmp;
		}
		else {
			size = 1;
			arr = new T[size-1];
		}
	}
	arr[col_elem] = elem;
	col_elem += 1;
}

template<typename T>
void My_vector<T>::swap(My_vector& vector) {
	help::swap(arr, vector.arr);
	help::swap(col_elem, vector.col_elem);
	help::swap(size, vector.size);
}

//template <typename T1 = time_t, typename T2 = std::string, typename T3 = long>
//using Default_Node = My_vector<T1, T2, T3>;


