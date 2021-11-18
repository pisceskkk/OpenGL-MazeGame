#pragma once
#include "../utils/model.h"

class Key:Model{
public:
    GLfloat zoom=1.0;
    using Model::Model;
    void Draw();
    void Draw(GLfloat angle);
};
