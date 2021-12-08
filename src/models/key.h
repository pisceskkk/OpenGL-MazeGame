#pragma once
#include "../utils/model.h"

class Key:Model{
public:
    GLfloat zoom=1.0;
    using Model::Model;
    using Model::Init;
    void Draw();
    void Draw(GLfloat angle);
};
