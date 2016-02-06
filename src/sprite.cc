#include "sprite.h"

void Sprite::next()
{
    static bool is_init{false};
    if (!is_init) {
	_it = _quaduvlist.begin();
	is_init = true;
    } else {
	if (++_it == _quaduvlist.end()) _it = _quaduvlist.begin();
    }
}

