#pragma once

#include "../program/program.h"
#include "../mesh/mesh.h"
#include "../texture/texture.h"
#include "../sprite/sprite.h"

struct EntityResources {
    Program program;
    Mesh mesh;
    Texture texture;
    Sprite sprite;
};
