#pragma once
#include "stb_image.h"
#include <string>
#include <iostream>
#include <GL/freeglut.h>

class Texture{
private:
public:
    GLuint id;
    char* name;
    Texture();
    Texture(const char* img_path);
    void Load(const char* img_path);
    void Load();
    void Activate();
};
