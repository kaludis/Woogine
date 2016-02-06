#pragma once

#include <GL/glew.h>

struct Mesh {
    GLuint buffer_id;
    GLuint texbuffer_id;
    GLuint indexbuffer_id;
    GLuint index_count;
};
