template<typename Data>
concept Valid_Data_ = requires(Data data, Data tmp_data) {
	requires std::destructible<Data>
&& std::movable<Data>
&& std::copy_constructible<Data>
&& std::move_constructible<Data>;
};

template<typename... Data>
concept Valid_Data = (Valid_Data_ <Data> && ...);


template<typename Finder, typename... Types>
struct Index;

template<typename Head, typename... Tail>
struct Index<Head, Head, Tail...> {
	static constexpr size_t value = 1;
};

template<typename Finder, typename Head, typename... Tail>
struct Index<Finder, Head, Tail...> {
	static constexpr size_t value = Index<Finder, Tail...>::value + 1;
};

template<typename Finder>
struct Index<Finder> {
	static_assert(false, "Not found index");
};


template <Valid_Data_ Finder, Valid_Data... Types>
struct ValueType;

template <Valid_Data_ Finder, Valid_Data_ Head, Valid_Data... Tail>
struct ValueType<Finder, Head, Tail...> {
	using Type = ValueType<Finder, Tail...>::Type;
};

template <Valid_Data_ Finder, Valid_Data... Tail>
struct ValueType<Finder, Finder, Tail...> {
	using Type = Finder;
};


template <size_t index, Valid_Data... Types>
struct ValueIndex;

template <size_t index, Valid_Data_ Head, Valid_Data... Tail>
struct ValueIndex<index, Head, Tail...> {
	using Type = ValueIndex<index-1, Tail...>::Type;
};

template <Valid_Data_ Head, Valid_Data... Tail>
struct ValueIndex<1, Head, Tail...> {
	using Type = Head;
};

