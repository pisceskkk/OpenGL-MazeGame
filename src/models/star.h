#pragma once
#include "../utils/model.h"

class Star:Model{
public:
    using Model::Model;
    using Model::Init;
    void Draw();
    void Draw(GLfloat angle);
};