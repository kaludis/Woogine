#pragma once

#include <string>
#include <exception>

class DataReaderException : public std::exception {
public:
    DataReaderException(const std::string& msg) noexcept;

    DataReaderException(const DataReaderException& another) noexcept;

    DataReaderException& operator=(const DataReaderException& another) noexcept;

    const char* what() const noexcept override;
    
private:
    std::string _msg;
};

inline
DataReaderException::DataReaderException(const std::string& msg) noexcept
    : _msg{msg}
{}

inline
DataReaderException::DataReaderException(const DataReaderException& another) noexcept
{
    _msg = another._msg;
}

inline
DataReaderException&
DataReaderException::operator=(const DataReaderException& another) noexcept
{
    if (this != &another) {
	_msg = another._msg;
    }

    return *this;
}

inline
const char* DataReaderException::what() const noexcept
{
    return _msg.c_str();
}
