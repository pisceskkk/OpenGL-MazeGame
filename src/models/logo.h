#pragma once
#include <cstring>
#include "../utils/vec.h"
#include "../utils/texture.h"

class Logo{
private:
    char *name;
    Texture texture;
public:
    Logo(char *filename){
        name = new char[strlen(filename) + 1];
        memcpy(name, filename, strlen(filename)+1);
    }
    void Load();
    void Draw(vec2 position, vec2 scale);
};