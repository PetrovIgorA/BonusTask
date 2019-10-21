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

template <class T>
struct PetrovAllocator {
    using value_type = T;

    PetrovAllocator() noexcept {}
    template <class U> PetrovAllocator (const PetrovAllocator<U>&) noexcept {}
    
    T* allocate (std::size_t n) {
        return static_cast<T*>( A::operator new(n*sizeof(T)));
    }
    void deallocate (T* p, std::size_t n) {
        A::operator delete(p, n);
    }

};


int main() {
    PetrovAllocator<A> alloc;
    auto sp = std::allocate_shared<A>(alloc);
}