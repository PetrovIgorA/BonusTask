#include<ctime>
#include<vector>
#include<algorithm>

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

auto
MakePredicate(const Items& items)
{
    return [ items ] (int v) { 
        return std::find_if(items.cbegin(), items.cend(), 
                [v] (auto item) { return item.value == v; }) != items.cend();
    };
}