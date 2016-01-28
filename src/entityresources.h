#pragma once

#include "program.h"
#include "mesh.h"
#include "texture.h"

struct EntityResources {
    Program program;
    Mesh mesh;
    Texture texture;
};
