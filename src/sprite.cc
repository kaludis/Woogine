#include "sprite.h"

void Sprite::reset()
{
    _it = _quaduvlist.begin();
}

void Sprite::next()
{
    if (++_it == _quaduvlist.end()) _it = _quaduvlist.begin();
}

