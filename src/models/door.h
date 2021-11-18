#pragma once
#include "../utils/model.h"
#include "../utils/tools.h"
#include <GL/freeglut.h>

class Door:Model{
private:
    GLboolean is_open=0;
    GLfloat start_time, speed;

public:
    using Model::Model;
    void Draw();
    void Draw(GLfloat time);
    void open(GLfloat start_time, GLfloat speed);
};
