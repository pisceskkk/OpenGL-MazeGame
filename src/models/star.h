#pragma once
#include "../utils/model.h"

class Star:Model{
public:
    using Model::Model;
    void Draw();
    void Draw(GLfloat angle);
};