#pragma once
#include "vec.h"
#include <string>
#include <GL/freeglut.h>

//write texts
void DrawText(std::string text, void* font, vec3 color, vec2 postion);

//draw circle in 3D
void DrawCircle3D(vec3 center, vec3 normal, GLfloat radius, vec3 color, GLint slices);

//draw unit cube with/without texture
void DrawUnitCube(GLboolean use_texture);