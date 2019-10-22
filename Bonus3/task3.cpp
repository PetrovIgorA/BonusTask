#include <iostream>
#include <memory>

class A {
public:
// ...
static void * operator new(size_t size) {
std::cout << "operator new!" << std::endl;
return ::operator new(size);
}
static void operator delete(void *p, size_t size) {
std::cout << "operator delete!" << std::endl;
return ::operator delete(p);
}
};

template <class Some, class T>
struct PetrovAllocator {
    using value_type = Some;

    PetrovAllocator() noexcept {}
    template <class TT, class TTT> PetrovAllocator (const PetrovAllocator<TT, TTT>&) noexcept {}
    
    Some* allocate (std::size_t n) {
        return static_cast<Some*> (T::operator new(n * sizeof(T)));
    }
    void deallocate (Some* p, std::size_t n) {
        T::operator delete(p, n * sizeof(T));
    }

    ~PetrovAllocator() {}

};


int main() {
    auto sp = std::allocate_shared<A>(PetrovAllocator<A, A>());
}