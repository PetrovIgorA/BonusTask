#pragma once
class ComplexNumber
{
public:
    constexpr ComplexNumber() : real(0), imaginary(0) {}
    constexpr ComplexNumber(const ComplexNumber& other) : real(other.real), imaginary(other.imaginary) {}
    constexpr ComplexNumber(int realPart, int imaginaryPart) : real(realPart), imaginary(imaginaryPart) {}

    constexpr int GetRe() const { return real; }
    constexpr int GetIm() const { return imaginary; }

    constexpr void SetRe(int re) { real = re; }
    constexpr void SetIm(int im) { imaginary = im; }

    constexpr bool operator==(const ComplexNumber& other) const
    {
        return (real == other.real) && (imaginary == other.imaginary);
    }

private:
    int real, imaginary;
};
