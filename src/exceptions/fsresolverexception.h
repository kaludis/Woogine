#pragma once

#include <string>
#include <exception>

class FSResolverException : public std::exception {
public:
    FSResolverException(const std::string& msg) noexcept;

    FSResolverException(const FSResolverException& another) noexcept;

    FSResolverException& operator=(const FSResolverException& another) noexcept;

    const char* what() const noexcept override;
    
private:
    std::string _msg;
};

inline
FSResolverException::FSResolverException(const std::string& msg) noexcept
    : _msg{msg}
{}

inline
FSResolverException::FSResolverException(const FSResolverException& another) noexcept
{
    _msg = another._msg;
}

inline
FSResolverException&
FSResolverException::operator=(const FSResolverException& another) noexcept
{
    if (this != &another) {
	_msg = another._msg;
    }

    return *this;
}

inline
const char* FSResolverException::what() const noexcept
{
    return _msg.c_str();
}
