#pragma once

#include <map>
#include <vector>
#include <string>
#include <memory>

class Input {
public:
    using Keys = std::map<std::string, bool>;

private:
    using KeyStatePair = std::pair<const std::string, bool>;

public:
    Input();

    void reset();

    void set_keystate(const char* key, bool state);
    
    bool keystate(const char* key);

    bool in_motion() const;

    bool is_double_direction() const;

private:
    void _check_motion();
    
    void _check_double_direction();
    
private:
    Keys _keys;

    static const std::vector<std::string> _keys_names;

    bool _in_motion;
    
    bool _is_double_direction;
};

using InputPtr = std::unique_ptr<Input>;

inline
bool Input::keystate(const char* key)
{
    auto it = _keys.find(key);
    return (it == _keys.end()) ? false : it->second;
}

inline
void Input::set_keystate(const char* key, bool state)
{
    _keys[key] = state;
    
    _check_motion();    

    _check_double_direction();
}

inline
bool Input::in_motion() const
{
    return _in_motion;
}

inline
bool Input::is_double_direction() const
{
    return _is_double_direction;
}
