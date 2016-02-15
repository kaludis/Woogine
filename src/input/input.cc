#include "input.h"

Input::Input()
{
    for (const std::string& key_name : _keys_names) {
	_keys[key_name] = false;
    }
}

void Input::reset()
{
    for (KeyStatePair& kspair : _keys) {
	kspair.second = false;
    }
}

const std::vector<std::string> Input::_keys_names = {
    "kUp",
    "kDown",
    "kLeft",
    "kRight"
};
