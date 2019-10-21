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
struct MyAllocator {
    typedef T value_type;

    MyAllocator() noexcept {}
    template <class U> MyAllocator (const MyAllocator<U>&) noexcept {}
    
    T* allocate (std::size_t n) {
        return static_cast<T*>( A::operator new(n*sizeof(T)));
    }
    void deallocate (T* p, std::size_t n) {
        A::operator delete(p, n);
    }

};


int main() {
MyAllocator<A> alloc;
auto sp = std::allocate_shared<A>(alloc);
}