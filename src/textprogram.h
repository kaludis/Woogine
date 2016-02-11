#pragma once

#include <GL/glew.h>

struct TextProgram {
    GLuint program_id;
    GLint uniform_projection;
    GLint uniform_glyph;
    GLint uniform_textcolor;
    GLint attribute_texcoord;
};
