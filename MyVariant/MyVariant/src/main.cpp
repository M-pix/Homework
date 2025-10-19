
#include <iostream>

template <size_t index, typename... Types>
struct TypeIndex;

template <size_t index, typename Head, typename... Tail>
struct TypeIndex<index, Head, Tail...> {
	using Type = TypeIndex<index - 1, Tail...>::Type;
};

template <typename Head, typename... Tail>
struct TypeIndex<0, Head, Tail...> {
	using Type = Head;
};

int main()
{
	using type = TypeIndex<1,int,char>::Type;
	type a;
	std::cout << typeid(a).name();
	return 0;
}
