#include<iostream>
#include<map>
#include<vector>
#include<ctime>

// Two examples: forward and reverse ordering

// We have ordered vector and insert values
// from this vector in map. Here the insertion is always
// at the previous(1) or next(2) position

void saveOrderedVectorInMapWithHint(
        const std::vector<int>& vec,
        std::map<int, int> data)
{
    auto hint_iter = data.lower_bound(vec.size() - 1);
    for (size_t i = 0; i < vec.size(); ++i) {
        hint_iter = data.insert(hint_iter, { vec[0], vec[0] });
    }
}

void saveOrderedVectorInMapWithoutHint(
        const std::vector<int>& vec,
        std::map<int, int> data)
{
    for (size_t i = 0; i < vec.size(); ++i) {
        data.insert({ vec[0], vec[0] });
    }
}

constexpr size_t SIZE = 10000;
constexpr size_t COUNT_ITER = 2000;

int main()
{
    std::vector<int> vecForwardOrdered(SIZE);
    std::vector<int> vecReverseOrdered(SIZE);
    std::map<int, int> data;

    std::cout << "\nInsertion size: " << SIZE;
    std::cout << "\nIteration count: " << COUNT_ITER << std::endl;

    for (size_t i = 0; i < SIZE; ++i){
        data.insert({i, i});
    }
    for (size_t i = SIZE; i < 2 * SIZE; ++i){
        vecForwardOrdered[i - SIZE] = i;
        vecReverseOrdered[i - SIZE] = 3 * SIZE - i - 1;
    }
    for (size_t i = SIZE * 2; i < 3 * SIZE; ++i){
        data.insert({i, i});
    }

    std::cout << "\nTest 1: Forward ordering:\ntesting..." << std::endl;
    clock_t start = clock();
    for (size_t i = 0; i < COUNT_ITER; ++i) {
        saveOrderedVectorInMapWithoutHint(vecForwardOrdered, data);
    }
    std::cout << "Without hint: " << static_cast<double>(clock() - start) / CLOCKS_PER_SEC << " s" << std::endl;

    start = clock();
    for (size_t i = 0; i < COUNT_ITER; ++i) {
        saveOrderedVectorInMapWithHint(vecForwardOrdered, data);
    }
    std::cout << "With hint: " << static_cast<double>(clock() - start) / CLOCKS_PER_SEC << " s" << std::endl;

    std::cout << "\nTest 2: Reverse ordering:\ntesting..." << std::endl;
    start = clock();
    for (size_t i = 0; i < COUNT_ITER; ++i) {
        saveOrderedVectorInMapWithoutHint(vecReverseOrdered, data);
    }
    std::cout << "Without hint: " << static_cast<double>(clock() - start) / CLOCKS_PER_SEC << " s" << std::endl;

    start = clock();
    for (size_t i = 0; i < COUNT_ITER; ++i) {
        saveOrderedVectorInMapWithHint(vecReverseOrdered, data);
    }
    std::cout << "With hint: " << static_cast<double>(clock() - start) / CLOCKS_PER_SEC << " s" << std::endl;

    return 0;
}