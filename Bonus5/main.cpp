#include<iostream>
#include<algorithm>
#include<unordered_set>

#include "Range.hpp"

int main()
{
    Range r1(4, 48, 4);
    Range r2(23, -13, -6);
    Range r3(8, -6, 1);
    Range r4(8, -6, -1);

    std::unordered_set<Range, hashRange> ranges;

    ranges.insert(r1);
    ranges.insert(r2);
    ranges.insert(r3);
    ranges.insert(r4);

    for (auto& range : ranges) {
        std::cout << "\n[" << range.getStart() << ", ";
        std::cout << range.getStop() << ") with step = ";
        std::cout << range.getStep();
        std::cout << " (size = " << range.size() << "):\n";

        std::for_each(range.begin(), range.end(),
        [] (int64_t v)
        {
            std::cout << v << " ";
        });

        std::cout << "\n";
    }
    std::cout << std::endl;

    std::optional<int64_t> opt_value1 = r1[3];
    std::optional<int64_t> opt_value2 = r1[13];

    std::cout << "opt_value1 (must be correct): ";
    if (opt_value1) {
        std::cout << opt_value1.value() << std::endl;
    }
    else {
        std::cout << "incorrect index" << std::endl;
    }

    std::cout << "opt_value2 (must be incorrect): ";
    if (opt_value2) {
        std::cout << opt_value2.value() << std::endl;
    }
    else {
        std::cout << "incorrect index" << std::endl;
    }
    std::cout << std::endl;

    try {
        std::cout << "Must be error (not exist value)" << std::endl;
        auto i = r1.end();
        auto v = *i;
        std::cout << v << std::endl;
    }
    catch(std::exception& ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
    }

    try {
        std::cout << "Must be error (prefix ++)" << std::endl;
        auto i = r1.end();
        auto v = ++i;
        std::cout << *v << std::endl;
    }
    catch(std::exception& ex) {
        std::cerr<< "Error: " << ex.what() << std::endl;
    }

    try {
        std::cout << "Must be error (postfix ++)" << std::endl;
        auto i = r1.end();
        auto v = i++;
        std::cout << *v << std::endl;
    }
    catch(std::exception& ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
    }

    try {
        std::cout << "Must be error (step = 0):" << std::endl;
        Range rStepZero(1, 5, 0);
        std::cout << rStepZero.getStep() << std::endl;
    }
    catch(std::exception& ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
    }


    std::cout << std::endl;

    return 0;
}