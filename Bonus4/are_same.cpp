#include<type_traits>
#include<iostream>

// no comments because ochev

template<class T, class... Tail>
struct are_same : public std::false_type {};

template<class FirsType, class SecondType>
struct are_same<FirsType, SecondType> : public std::is_same<FirsType, SecondType> {};

template<class T, class TT, class... Tail>
struct are_same<T, TT, Tail...>
: public std::bool_constant<std::is_same_v<T, TT> && are_same<T, Tail...>::value >
{
};

template<class... Args>
constexpr bool are_same_v = are_same<Args...>::value;


int main()
{
    std::cout << are_same_v<int, int32_t, signed int> << std::endl; // true
    std::cout << are_same_v<char, int, bool> << std::endl;          // false

    return 0;
}

