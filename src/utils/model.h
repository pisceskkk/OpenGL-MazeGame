#pragma once
#include "material.h"
#include "Texture.h"
#include "vec.h"
#include <GL/freeglut.h>

class Model
{
public:
    vec3 position;
    vec3 normal;
    Material material;
    Texture* texture;
    GLboolean use_material=0, use_texture=0;

    Model(){memset(this,0,sizeof(Model)); normal=kZAxis;}
    Model(vec3 p) {this->position = p;}
    Model(vec3 p, vec3 n):
        position(p), normal(n.normalize()){}
    Model(vec3 p, vec3 n, Material m):
        position(p), normal(n.normalize()), material(m), use_material(1) {}
    Model(vec3 p, vec3 n, Texture* t):
        position(p), normal(n.normalize()), texture(t), use_texture(1) {}
    Model(vec3 p, vec3 n, Material m, Texture* t):
        position(p), normal(n.normalize()),material(m), use_material(1), texture(t), use_texture(1) {}
    void Draw();
};