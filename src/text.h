#pragma once

#include "textprogram.h"
#include "textmesh.h"
#include "point.hpp"

#include <string>

#include <GL/glew.h>

#include <glm/glm.hpp>

class EntityCreator;

class Text {
    friend EntityCreator;
    
public:
    Text(const std::string& text, const Point2f& position,
	 float scale, const glm::vec3& color)
	: _text{text},
	_position{position},
	_scale{scale},
	_color(color)
    {}

    TextProgram program() const;

    Point2f position() const;

    void set_text(const std::string& text);
    
    std::string text() const;

    float scale() const;

    glm::vec3 color() const;

    TextMesh mesh() const;

private:
    TextProgram _program;
    std::string _text;    
    Point2f _position;
    float _scale;
    glm::vec3 _color;
    TextMesh _mesh;
};

inline
TextProgram Text::program() const
{
    return _program;
}

inline
Point2f Text::position() const
{
    return _position;
}

inline
void Text::set_text(const std::string& text)
{
    _text = text;
}

inline
std::string Text::text() const
{
    return _text;
}

inline
float Text::scale() const
{
    return _scale;
}

inline
glm::vec3 Text::color() const
{
    return _color;
}

inline
TextMesh Text::mesh() const
{
    return _mesh;
}
