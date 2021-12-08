#pragma once
#include "vec.h"
#include <GL/freeglut.h>

class Camera
{
public:
    vec3 position;
    vec3 direction;
    vec3 up;
    vec3 right;
    vec3 rotation;
    float speed;
    Camera(){
        position = kZeroVec3;
        direction = kXAxis;
        up = kZAxis;
        right = kYAxis;
        rotation = kZeroVec3;
        speed = 0;
    }
    Camera(vec3 position, vec3 direction, vec3 up, vec3 right):
        position(position),direction(direction),up(up),right(right){
        rotation = kZeroVec3;
        speed = 0;
    }

    Camera(vec3 position, vec3 direction, vec3 up, vec3 right, vec3 rotation, float speed):
        position(position),direction(direction),up(up),right(right),rotation(rotation),speed(speed){}

    void Move(vec3 direction);
    void MoveForward();
    void MoveBackward();
    void MoveRight();
    void MoveLeft();
    void MoveUp();
    void MoveDown();
    void TurnLeft();
    void TurnRight();
    void Go(float distance);
    void RotateX(float angle);
    void RotateY(float angle);
    void RotateZ(float angle);
};