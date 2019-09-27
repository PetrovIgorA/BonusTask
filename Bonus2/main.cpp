#include<iostream>
#include<assert.h>

#include "TItem.hpp"

void printItems(const Items& items)
{
    if (items.size() == 0) {
        std::cout << std::endl;
        return;
    }
    for (int i = 0; i < items.size() - 1; ++i) {
        std::cout << items[i].value << " " << items[i].timestamp << ", ";
    }
    std::cout << items[items.size() - 1].value << " " << items[items.size() - 1].timestamp;
    std::cout << std::endl << std::endl;
}

int main()
{
    Items items = MakeItemsSimple<0, 1, 4, 5, 6>();
    Items newItems = MakeItemsSimple<7, 15, 1>();
    Items emptyItems = MakeItemsSimple<>();
    printItems(items);
    printItems(newItems);
    printItems(emptyItems);

    auto isFound = MakePredicate(items);
    auto isFoundNew = MakePredicate(newItems);
    auto isFound_r = MakePredicate_r(items);
    auto isFoundNew_r = MakePredicate_r(newItems);
    assert(isFound(0) == true);    assert(isFound_r(0) == true);
    assert(isFound(7) == false);   assert(isFound_r(7) == false);
    assert(isFoundNew(7) == true); assert(isFoundNew_r(7) == true);
    assert(isFoundNew(6) == false);assert(isFoundNew_r(6) == false);

    return 0;
}