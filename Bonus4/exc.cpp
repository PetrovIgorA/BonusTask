#include<gtest/gtest.h>

#include "TMyException.hpp"

int divInt(int x, int y)
{
    if (y == 0) {
        throw ZeroDivision();
    }

    return x / y;
}

int sumPosNum(int x, int y)
{
    if (x > INT32_MAX - y) {
        throw OverflowException();
    }

    return x + y;
}

int negSubPos(int x, int y)
{
    if (INT32_MIN + y > x) {
        throw UnderflowException();
    }

    return x - y;
}

int some(int x, int y)
{
    if (y == 0 || x > INT32_MAX - y) {
        throw TMyException();
    }
    return (x + y) / y;
}

TEST(checkException, TMyException_test)
{
    EXPECT_THROW(some(8, 0), TMyException);
    EXPECT_THROW(some(INT32_MAX - 9, 21), TMyException);

    EXPECT_NO_THROW(some(11, 100));

    try {
        some(0, 0);
        FAIL() << "no exception for TMyException";
    }
    catch(TMyException& ex) {
        EXPECT_STREQ(ex.what(), "TMyException");
    }
    catch(...) {
        FAIL() << "not TMyException";
    }
}

TEST(checkException, zeroDiv_test)
{
    EXPECT_THROW(divInt(8, 0), ZeroDivision);
    EXPECT_THROW(divInt(-9, 0), ZeroDivision);
    EXPECT_THROW(divInt(0, 0), ZeroDivision);

    EXPECT_NO_THROW(divInt(9, 9));

    try {
        divInt(100, 0);
        FAIL() << "no exception for ZeroDivision";
    }
    catch(TMyException& ex) {
        EXPECT_STREQ(ex.what(), "zero division");
    }
    catch(...) {
        FAIL() << "not ZeroDivision";
    }
}

TEST(checkException, Overflow_test)
{
    EXPECT_THROW(sumPosNum(INT32_MAX - 1, 3), OverflowException);
    EXPECT_THROW(sumPosNum(INT32_MAX - 9, 21), OverflowException);
    EXPECT_NO_THROW(sumPosNum(78, 87));

    EXPECT_NO_THROW(sumPosNum(INT32_MAX - 100, 50));

    try {
        sumPosNum(INT32_MAX, 9);
        FAIL() << "no exception for OverflowException";
    }
    catch(TMyException& ex) {
        EXPECT_STREQ(ex.what(), "overflow exception");
    }
    catch(...) {
        FAIL() << "not OverflowException";
    }
}

TEST(checkException, Underflow_test)
{
    EXPECT_THROW(negSubPos(INT32_MIN + 1, 3), UnderflowException);
    EXPECT_THROW(negSubPos(INT32_MIN + 9, 21), UnderflowException);
    EXPECT_NO_THROW(negSubPos(78, 87));

    EXPECT_NO_THROW(negSubPos(INT32_MIN + 8, 2));

    try {
        negSubPos(INT32_MIN, 9);
        FAIL() << "no exception for UnderflowException";
    }
    catch(TMyException& ex) {
        EXPECT_STREQ(ex.what(), "underflow exception");
    }
    catch(...) {
        FAIL() << "not UnderflowException";
    }
}

TEST(operatorOutputTest, singleTest)
{
    // Arrange

    TMyException my_exc;
    ZeroDivision zero_div;
    OverflowException of_exc;
    UnderflowException uf_exc;

    // Action

    my_exc << "Some error 1";
    zero_div << "Some error 2";
    of_exc << "Some error 3";
    uf_exc << "Some error 4";

    // Assert

    EXPECT_STREQ(my_exc.what(), "Some error 1");
    EXPECT_STREQ(zero_div.what(), "Some error 2");
    EXPECT_STREQ(of_exc.what(), "Some error 3");
    EXPECT_STREQ(uf_exc.what(), "Some error 4");
}

int main(int argc, char ** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}