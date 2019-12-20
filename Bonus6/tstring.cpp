#include<cassert>
#include<cstddef>

template<char... c>
struct TString
{
    constexpr TString () {}

};

template<char... left, char ... right>
constexpr bool
operator== (const TString<left...>&, const TString<right...>& ) noexcept
{
    if constexpr (sizeof...(left) != sizeof...(right)) {
        return false;
    }
    else {
        char str1[sizeof...(left)] = {left...};
        char str2[sizeof...(right)] = {right...};

        for (size_t i = 0; i < sizeof...(left); ++i) {
            if (str1[i] != str2[i]) {
                return false;
            }
        }

        return true;
    }
}

template<char... left, char... right>
constexpr TString<left..., right...>
operator+(const TString<left...>& , const TString<right...>& ) noexcept
{
    return TString<left..., right...>();
}

template<class TChar, TChar... args>
constexpr auto
operator"" _s ()
{
    return TString<args...>();
}


int main()
{
    constexpr auto hello = "hello"_s + " world"_s;
    static_assert(hello == "hello world"_s);

    return 0;
}