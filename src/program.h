#pragma once

#include <GL/glew.h>

struct Program {
    GLuint program_id;
    GLint attrib_coord3d;
    GLint attrib_texcoord;
    GLint uniform_projection;
    GLint uniform_view;
    GLint uniform_model;
    GLint uniform_sampler2d;
};
