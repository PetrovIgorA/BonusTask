#include<iostream>
#include<algorithm>

#include "Range.hpp"

int main()
{
    Range r1(4, 48, 4);
    Range r2(23, -13, -6);

    std::cout << "\nr1 (size = " << r1.size() << "):\n";
    std::for_each(r1.begin(), r1.end(),
    [] (int64_t v)
    {
        std::cout << v << " ";
    });
    std::cout << std::endl;

    std::cout << "\nr2 (size = " << r2.size() << "):\n";
    std::for_each(r2.begin(), r2.end(),
    [] (int64_t v)
    {
        std::cout << v << " ";
    });
    std::cout << "\n\n";

    std::optional<int64_t> opt_value1 = r1[3];
    std::optional<int64_t> opt_value2 = r1[13];

    std::cout << "opt_value1: ";
    if (opt_value1) {
        std::cout << opt_value1.value() << std::endl;
    }
    else {
        std::cout << "incorrect index" << std::endl;
    }

    std::cout << "opt_value2: ";
    if (opt_value2) {
        std::cout << opt_value2.value() << std::endl;
    }
    else {
        std::cout << "incorrect index" << std::endl;
    }
    std::cout << std::endl;

    try {
        auto i = r1.end();
        auto v = *i;
        std::cout << v << std::endl;
    }
    catch(std::exception& ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
    }

    try {
        auto i = r1.end();
        auto v = ++i;
        std::cout << *v << std::endl;
    }
    catch(std::exception& ex) {
        std::cerr<< "Error: " << ex.what() << std::endl;
    }

    try {
        auto i = r1.end();
        auto v = i++;
        std::cout << *v << std::endl;
    }
    catch(std::exception& ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
    }

    std::cout << std::endl;

    return 0;
}