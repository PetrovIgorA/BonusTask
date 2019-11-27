#include<iostream>
#include<string>

#include "Any.hpp"

int main()
{
    Any a(5);

    std::cout << a.get<int>() << std::endl;

    try {
        a.get<std::string>();
    }
    catch(std::exception& ex) {
        std::cerr << ex.what() << std::endl;
    }   

    return 0;
}