#pragma once

#include "vertexattributes.h"
#include "texture.h"
#include "debug.h"

#include <vector>
#include <memory>

class ResourceManager;

class Sprite {
public:
    friend ResourceManager;

    struct QuadUV {
	UVCoords bottom_left;
	UVCoords bottom_right;
	UVCoords top_right;
	UVCoords top_left;
    };

    using QuadUVList = std::vector<QuadUV>;

private:
    using QuadUVListIter = typename QuadUVList::const_iterator;

public:
    void next();

     QuadUV quaduv() const;

    GLuint buffer_id() const;

    GLuint texture_id() const;
    
private:
    QuadUVList _quaduvlist;
    QuadUVListIter _it;
    
    GLuint _buffer_id;
    GLuint _texture_id;
};

using SpritePtr = std::unique_ptr<Sprite>;

inline
GLuint Sprite::buffer_id() const
{
    return _buffer_id;
}

inline
GLuint Sprite::texture_id() const
{
    return _texture_id;
}

inline
 Sprite::QuadUV Sprite::quaduv() const
{
    return *_it;
}
