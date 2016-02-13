#pragma once

#include <string>
#include <exception>

class WindowException : public std::exception {
public:
    WindowException(const std::string& msg) noexcept;

    WindowException(const WindowException& another) noexcept;

    WindowException& operator=(const WindowException& another) noexcept;

    const char* what() const noexcept override;
    
private:
    std::string _msg;
};

inline
WindowException::WindowException(const std::string& msg) noexcept
    : _msg{msg}
{}

inline
WindowException::WindowException(const WindowException& another) noexcept
{
    _msg = another._msg;
}

inline
WindowException&
WindowException::operator=(const WindowException& another) noexcept
{
    if (this != &another) {
	_msg = another._msg;
    }

    return *this;
}

inline
const char* WindowException::what() const noexcept
{
    return _msg.c_str();
}
