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

private:
    Keys _keys;

    static const std::vector<std::string> _keys_names;    
};

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
}

using InputPtr = std::unique_ptr<Input>;
