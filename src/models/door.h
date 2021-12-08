#pragma once
#include "../utils/model.h"
#include "../utils/tools.h"
#include <GL/freeglut.h>

class Door:Model{
private:
    GLboolean is_open=0;
    GLfloat start_time, speed, end_time;

public:
    using Model::Model;
    void Draw();
    void Draw(GLfloat time);
    void Open(GLfloat start_time, GLfloat speed);
    bool Check(GLfloat time);
    Door* Init(vec3 p, vec3 n, Material m){
        position = p;
        normal = n;
        material = m;
        use_material = 1;
        use_texture = 0;
        is_open = 0;
        return this;
    }
    Door* Init(vec3 p, vec3 n, Texture* t){
        position = p;
        normal = n;
        use_material = 0;
        texture = t;
        use_texture = 1;
        is_open = 0;
        return this;
    }
};
