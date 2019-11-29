#include<type_traits>
#include<iostream>

/*
    if I cann't use std::bool_constant then
    I write my bool_constant:

    template<bool T> struct bool_constant;
    template<> struct bool_constant<true> : public std::true_type {};
    template<> struct bool_constant<false> : public std::false_type {};

    It's work!
*/

template<class... Tail>
struct are_same;

template<class FirstType, class SecondType>
struct are_same<FirstType, SecondType>
: public std::is_same<std::decay_t<FirstType>, std::decay_t<SecondType>> {};

template<class T, class TT, class... Tail>
struct are_same<T, TT, Tail...>
: public std::bool_constant<std::is_same_v<std::decay_t<T>, std::decay_t<TT>> && are_same<T, Tail...>::value >
{
};

template<class... Args>
constexpr bool are_same_v = are_same<Args...>::value;


int main()
{
    // true
    std::cout << are_same_v<int, int32_t, signed int> << std::endl;
    // true
    std::cout << are_same_v<int, int32_t&, const signed int, const int&> << std::endl;
    // false
    std::cout << are_same_v<char, int, bool> << std::endl;

    return 0;
}

