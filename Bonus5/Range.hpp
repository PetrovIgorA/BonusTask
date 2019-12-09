#include<optional>
#include<cstdint>
#include<stdexcept>
#include<iterator>
#include<functional>

class Range;
struct hashRange;

class ForwardIteratorRange
{
public:
    using iterator_category = std::forward_iterator_tag;
    using value_type = int64_t;
    using difference_type = int64_t;
    using pointer = const int64_t *;
    using reference = const int64_t&;

    friend class Range;

    ForwardIteratorRange() : range_ptr(nullptr) {}

    ForwardIteratorRange& operator++ ();
    ForwardIteratorRange operator++ (int);
    bool operator== (const ForwardIteratorRange&) const noexcept;
    bool operator!= (const ForwardIteratorRange&) const noexcept;
    value_type operator* () const;

private:
    const Range * range_ptr;
    uint64_t index;

    ForwardIteratorRange(const Range * r_ptr, uint64_t i = 0)
        : range_ptr(r_ptr),
          index(i)
    {
    }
};

// Range(M, N, s)
// [M, N) with step = s
class Range
{
public:
    using const_iterator = ForwardIteratorRange;
    friend class hashRange;

    explicit Range(int64_t);
    Range(int64_t, int64_t, int64_t = 1);
    Range(const Range&) = default;
    Range(Range&&) = default;

    Range& operator= (const Range&) = default;
    Range& operator= (Range&&) = default;

    bool operator== (const Range&) const noexcept;

    int64_t getStart() const noexcept { return start; }
    int64_t getStop() const noexcept { return stop; }
    int64_t getStep() const noexcept { return step; }

    uint64_t size() const noexcept;
    std::optional<int64_t> operator[] (uint64_t) const noexcept;
    const_iterator begin() const noexcept;
    const_iterator end() const noexcept;

private:
    int64_t start, stop, step;
};

struct hashRange
{
    size_t
    operator() (const Range& _range) const noexcept
    {
        std::hash<int64_t> hashInt;
        return hashInt(_range.start) ^ hashInt(_range.stop) ^ hashInt(_range.step);
    }
};

Range::Range(int64_t _stop) : start(0), stop(_stop), step(1)
{
}

Range::Range(int64_t _start, int64_t _stop, int64_t _step) : start(_start), stop(_stop)
{
    if (_step == 0) {
        throw std::invalid_argument("step = 0");
    }
    step = _step;
}

bool
Range::operator== (const Range& other) const noexcept
{
    return (start == other.start) && (stop == other.stop) && (step == other.step);
}

uint64_t
Range::size() const noexcept
{
    if (step > 0) {
        if (start < stop) {
            return (stop - start - 1) / step + 1;
        }
        else {
            return 0;
        }
    }

    if (start > stop) {
        return (start - stop - 1) / -step + 1;
    }

    return 0;
}

std::optional<int64_t>
Range::operator[] (uint64_t i) const noexcept
{
    if (i >= size()) {
        return {};
    }

    return start + i * step;
}

Range::const_iterator
Range::begin() const noexcept
{
    return const_iterator(this);
}

Range::const_iterator
Range::end() const noexcept
{
    return const_iterator(this, size());
}

ForwardIteratorRange&
ForwardIteratorRange::operator++ ()
{
    if (index == range_ptr->size()) {
        throw std::out_of_range("prefix ++: out of Range");
    }

    ++index;

    return *this;
}

ForwardIteratorRange
ForwardIteratorRange::operator++ (int)
{
    if (index == range_ptr->size()) {
        throw std::out_of_range("postfix ++: out of Range");
    }

    ForwardIteratorRange ret_iterator(range_ptr, index);

    ++index;

    return ret_iterator;
}

bool
ForwardIteratorRange::operator== (const ForwardIteratorRange& other) const noexcept
{
    return index == other.index;
}

bool
ForwardIteratorRange::operator!= (const ForwardIteratorRange& other) const noexcept
{
    return index != other.index;
}

ForwardIteratorRange::value_type
ForwardIteratorRange::operator* () const
{
    std::optional<value_type> tmp = range_ptr->operator[](index);

    if (tmp.has_value() == false) {
        throw std::out_of_range("not exist value for dereferenced iterator");
    }

    return tmp.value();
}