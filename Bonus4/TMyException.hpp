#ifndef TMYEXCEPTION_HPP
#define TMYEXCEPTION_HPP

#include<exception>
#include<stdexcept>
#include<iostream>
#include<string>

class TMyException : public std::logic_error
{
public:
    TMyException() : std::logic_error(""), message_error("TMyException") {}
    TMyException(const char * msg) : std::logic_error(msg), message_error(msg) {}
    TMyException(const std::string& msg) : std::logic_error(msg), message_error(msg) {}

    virtual void operator<< (const std::string&);
    virtual const char * what() const noexcept override;

    virtual ~TMyException() noexcept {}
protected:
    std::string message_error;
};

void
TMyException::operator<< (const std::string& msg_err)
{
    message_error = msg_err;
}

const char *
TMyException::what() const noexcept
{
    return message_error.c_str();
}

class ZeroDivision : public TMyException
{
public:
    ZeroDivision() { message_error = "zero division"; }
    ZeroDivision(const char * msg) : TMyException(msg) {}
    ZeroDivision(const std::string& msg) : TMyException(msg) {}

    virtual ~ZeroDivision() noexcept {}
};

class OverflowException : public TMyException
{
public:
    OverflowException() { message_error = "overflow exception"; }
    OverflowException(const char * msg) : TMyException(msg) {}
    OverflowException(const std::string& msg) : TMyException(msg) {}

    virtual ~OverflowException() noexcept {}
};

class UnderflowException : public TMyException
{
public:
    UnderflowException() { message_error = "underflow exception"; }
    UnderflowException(const char * msg) : TMyException(msg) {}
    UnderflowException(const std::string& msg) : TMyException(msg) {}

    virtual ~UnderflowException() noexcept {}
};

#endif // TMYEXCEPTION_HPP