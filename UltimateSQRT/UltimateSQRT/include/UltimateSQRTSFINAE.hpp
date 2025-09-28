#pragma once
#include <type_traits>  
#include <iterator>     
#include <utility>      
#include <cmath>        
#include <iostream>     


template <typename... Ts> struct voider { using type = void; };
template <typename... Ts> using void_t = typename voider<Ts...>::type;


template <typename T> struct isPair : std::false_type {};
template <typename T1, typename T2> struct isPair<std::pair<T1, T2>> : std::true_type {};


template <typename T> constexpr bool isPair_v = isPair<std::remove_cvref_t<T>>::value;

template <typename T, typename = void> struct hasBegin : std::false_type {};
template <typename T>
struct hasBegin<T, void_t<decltype(std::begin(std::declval<T&>()))>> : std::true_type {};


template <typename T, typename = void> struct hasEnd : std::false_type {};
template <typename T>
struct hasEnd<T, void_t<decltype(std::end(std::declval<T&>()))>> : std::true_type {};


template <typename T, typename Ref = void> struct hasRef : std::false_type {};
template <typename T>
struct hasRef<T, typename T::reference> : std::true_type {};


template <typename It, typename = void> struct InputIter : std::false_type {};
template <typename It>
struct InputIter<It, void_t<
    decltype(*std::declval<It&>()),  
    decltype(++std::declval<It&>())  
    >> : std::bool_constant<!std::is_array_v<std::remove_cvref_t<It>>> {};

template <typename Sentinel, typename It, typename = void> struct sentinel : std::false_type {};
template <typename Sentinel, typename It>
struct sentinel<Sentinel, It, void_t<decltype(std::declval<It&>() == std::declval<Sentinel&>())>> : std::true_type {};


template <typename Data, typename = void> struct pairElem : std::false_type {};
template <typename Data>
struct pairElem<Data, std::enable_if_t<hasBegin<Data>::value, void>>
    : isPair<decltype(*std::begin(std::declval<Data&>()))> {
};

template <typename Data> constexpr bool is_pair_element_v = pairElem<Data>::value;


template <typename Data, typename = void> struct baseContainer : std::false_type {};
template <typename Data>
struct baseContainer<Data, std::enable_if_t<
    hasBegin<Data>::value &&
    hasEnd<Data>::value &&
    InputIter<decltype(std::begin(std::declval<Data&>()))>::value &&
    sentinel<decltype(std::end(std::declval<Data&>())), decltype(std::begin(std::declval<Data&>()))>::value
    >> : std::true_type {};

template <typename Data> constexpr bool is_container_base_v = baseContainer<Data>::value;


// Базовый шаблон с дефолтным значением false
template <typename Data, typename = void>
struct MutableIterable : std::false_type {};

// Специализация через SFINAE
template <typename Data>
struct MutableIterable<Data,
    void_t<
    decltype(*std::begin(std::declval<Data&>()))
    >>
    : std::bool_constant<
    std::is_same_v<
    decltype(*std::begin(std::declval<Data&>())),
    typename Data::reference
    >&&
    std::is_assignable_v<
    typename Data::reference,
    double
    >
    > {};

// Удобная константа для использования
template <typename Data>
inline constexpr bool is_mutable_iterable_v = MutableIterable<Data>::value;



template <typename Data, typename = void> struct container : std::false_type {};
template <typename Data>
struct container<Data, std::enable_if_t<
    is_container_base_v<Data> &&
    is_mutable_iterable_v<Data> &&
    !is_pair_element_v<Data>
    >> : std::true_type {};

template <typename Data> constexpr bool is_container_v = container<Data>::value;


template <typename Data, typename = void> struct containerConst : std::false_type {};
template <typename Data>
struct containerConst<Data, std::enable_if_t<
    is_container_base_v<Data> &&
    !is_mutable_iterable_v<Data> &&
    !is_pair_element_v<Data>
    >> : std::true_type {};

template <typename Data> constexpr bool is_container_const_v = containerConst<Data>::value;


template <typename Data, typename = void> struct is_container_key_value : std::false_type {};
template <typename Data>
struct is_container_key_value<Data, std::enable_if_t<
    is_mutable_iterable_v<Data>&&
    is_container_base_v<Data>&&
    is_pair_element_v<Data>
    >> : std::true_type {};

template <typename Data> constexpr bool is_container_key_value_v = is_container_key_value<Data>::value;


template <typename Data, typename = void> struct standart : std::false_type {};
template <typename Data>
struct standart<Data, std::enable_if_t<
    !is_container_base_v<Data> &&
    !is_container_const_v<Data> &&
    !is_container_key_value_v<Data> &&
    std::is_arithmetic<Data> :: value
    >> : std::true_type {};

template <typename Data> constexpr bool standart_v = standart<Data>::value;


template <typename Data,
    std::enable_if_t<standart_v<Data>, int>* = nullptr>
void ultimateSQRT(Data& data) {
    data = std::sqrt(data);
}

template <typename Data,
    std::enable_if_t<is_container_v<Data>, int>* = nullptr>
void ultimateSQRT(Data& data) {
    for (auto& elem : data) {
        elem = std::sqrt(elem);
    }
}

template <typename Data,
    std::enable_if_t<is_container_const_v<Data>, int>* = nullptr>
void ultimateSQRT(Data& data) {
    using ContainerType = std::remove_reference_t<Data>;
    ContainerType tmp;
    for (auto& elem : data) {  
        tmp.insert(std::sqrt(elem));  
    }
    data = tmp; 
}


template <typename Data,
    std::enable_if_t<is_container_key_value_v<Data>, int>* = nullptr>
void ultimateSQRT(Data& data) {
    for (auto& pair : data) {
        pair.second = std::sqrt(pair.second);
    }
}
