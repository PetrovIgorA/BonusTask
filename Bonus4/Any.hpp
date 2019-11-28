#include<memory>
#include<exception>
#include<utility>
#include<typeinfo>

// bad cast from any to concretely type
class Bad_Any_cast : public std::bad_cast
{
public:
    Bad_Any_cast() noexcept {}

    virtual const char * what() const noexcept override { return "bad Any cast"; }

    virtual ~Bad_Any_cast() noexcept {}
};

class Any
{
public:

    constexpr Any() noexcept : value_ptr(nullptr) {}
    Any(const Any&);
    Any(Any&&) noexcept;
    template<class T> Any(const T&);

    Any& operator= (const Any&);
    Any& operator= (Any&&) noexcept;
    template<class T> Any& operator= (const T&);

    // get value (get<type>)
    template<class T> T get() const;
    // is not empty?
    bool has_value() const noexcept;
    // remove value, is empty
    void reset() noexcept;

    ~Any() {}

private:
    class Any_value
    {
    public:
        virtual ~Any_value() {}
    };

    // class for storage concretely type
    template<class T>
    class ConcretelyValue : public Any_value
    {
    public:
        T value;

        ConcretelyValue(const T&);
    };

    std::shared_ptr<Any_value> value_ptr;
};

template<class T>
Any::ConcretelyValue<T>::ConcretelyValue(const T& _value) : value(_value)
{
}

Any::Any(const Any& other)
{
    value_ptr = other.value_ptr;
}

Any::Any(Any&& other) noexcept
{
    value_ptr = nullptr;
    std::swap(value_ptr, other.value_ptr);
}

template<class T>
Any::Any(const T& value)
: value_ptr(std::make_shared<ConcretelyValue<T>>(value))
{
}

Any&
Any::operator= (const Any& rhs)
{
    value_ptr = rhs.value_ptr;
    return *this;
}

Any&
Any::operator= (Any&& rhs) noexcept
{
    std::swap(value_ptr, rhs.value_ptr);
    return *this;
}

template<class T>
Any&
Any::operator= (const T& rhs)
{
    *this = Any(rhs);
    return *this;
}

template<class T>
T
Any::get() const
{
    ConcretelyValue<T> * try_value = dynamic_cast<ConcretelyValue<T> *>(value_ptr.get());

    if (try_value == nullptr) {
        throw Bad_Any_cast();
    }
    
    return try_value->value;
}

bool
Any::has_value() const noexcept
{
    return value_ptr != nullptr;
}

void
Any::reset() noexcept
{
    if (value_ptr == nullptr) {
        return;
    }

    value_ptr = nullptr;
}