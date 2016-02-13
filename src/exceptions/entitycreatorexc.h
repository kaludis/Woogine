#pragma once

#include <string>
#include <exception>

class EntityCreatorException : public std::exception {
public:
    EntityCreatorException(const std::string& msg) noexcept;

    EntityCreatorException(const EntityCreatorException& another) noexcept;

    EntityCreatorException& operator=(const EntityCreatorException& another) noexcept;

    const char* what() const noexcept override;
    
private:
    std::string _msg;
};

inline
EntityCreatorException::EntityCreatorException(const std::string& msg) noexcept
    : _msg{msg}
{}

inline
EntityCreatorException::EntityCreatorException(const EntityCreatorException& another) noexcept
{
    _msg = another._msg;
}

inline
EntityCreatorException&
EntityCreatorException::operator=(const EntityCreatorException& another) noexcept
{
    if (this != &another) {
	_msg = another._msg;
    }

    return *this;
}

inline
const char* EntityCreatorException::what() const noexcept
{
    return _msg.c_str();
}
