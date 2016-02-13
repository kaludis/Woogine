#pragma once

#include <string>
#include <exception>

class ResourceManagerException : public std::exception {
public:
    ResourceManagerException(const std::string& msg) noexcept;

    ResourceManagerException(const ResourceManagerException& another) noexcept;

    ResourceManagerException& operator=(const ResourceManagerException& another) noexcept;

    const char* what() const noexcept override;
    
private:
    std::string _msg;
};

inline
ResourceManagerException::ResourceManagerException(const std::string& msg) noexcept
    : _msg{msg}
{}

inline
ResourceManagerException::ResourceManagerException(const ResourceManagerException& another) noexcept
{
    _msg = another._msg;
}

inline
ResourceManagerException&
ResourceManagerException::operator=(const ResourceManagerException& another) noexcept
{
    if (this != &another) {
	_msg = another._msg;
    }

    return *this;
}

inline
const char* ResourceManagerException::what() const noexcept
{
    return _msg.c_str();
}
