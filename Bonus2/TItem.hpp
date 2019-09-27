#include<ctime>
#include<vector>
#include<iostream>
#include<algorithm>
#include<functional>

struct TItem
{
    int value;
    time_t timestamp;

    TItem(int v) : value(v), timestamp(std::time(0)) {}
};

using Items = std::vector<TItem>;

template<int... T>
Items MakeItemsSimple()
{
    return {T...};
}

// std::find_if version (loop into find_if)
auto
MakePredicate(const Items& items)
{
    return [ items ] (int v) { 
        return std::find_if(items.cbegin(), items.cend(), 
                [v] (auto item) { return item.value == v; }) != items.cend();
    };
}

// recursive lambda version
auto MakePredicate_r(const Items& items)
{
    return [items] (int v) -> bool
    {
        std::function<bool (size_t, int)> fun = [&fun, items] (size_t i, int v) -> bool
        {
            if (i == items.size()) {
                return false;
            }
            if (items[i].value == v) {
                return true;
            }
            return fun(i + 1, v);
        };

        return fun(0, v);
    };
}