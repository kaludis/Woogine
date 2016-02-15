#include "input.h"

Input::Input()
    : _in_motion{false},
    _is_double_direction{false}
{
    for (const std::string& key_name : _keys_names) {
	_keys[key_name] = false;
    }
}

void Input::reset()
{
    _in_motion = false;
    
    for (KeyStatePair& kspair : _keys) {
	kspair.second = false;
    }
}

void Input::_check_motion()
{
    if (_keys["kUp"] || _keys["kDown"] || _keys["kLeft"] || _keys["kRight"]) {
	_in_motion = true;
    } else {
	_in_motion = false;
    }
}

void Input::_check_double_direction()
{
    if (((_keys["kUp"]) && (_keys["kLeft"])) ||
	((_keys["kUp"]) && (_keys["kRight"])) ||
	((_keys["kDown"]) && (_keys["kLeft"])) ||
	((_keys["kDown"]) && (_keys["kRight"]))) {
	_is_double_direction = true;
    } else {
	_is_double_direction = false;
    }
}

const std::vector<std::string> Input::_keys_names = {
    "kUp",
    "kDown",
    "kLeft",
    "kRight"
};
