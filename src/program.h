#pragma once

#include <GL/glew.h>

struct Program {
    GLuint program_id;
    GLint attrib_coord3d;
    GLint attrib_texcoord;
    GLint uniform_mvp;
    GLint uniform_sampler2d;
};
