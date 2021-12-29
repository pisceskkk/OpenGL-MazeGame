#pragma once
#include "logo.h"

class Button{
private:
    bool enabled = true, is_on = false;
    Logo *on, *off;
    vec2 position;
    vec2 scale;
public:
    Button(Logo *on, Logo *off, vec2 position, vec2 scale):on(on),off(off), position(position), scale(scale){}
    void Draw();
    void Update(vec2 p, vec2 s);
    void On();
    void Off();
    bool In(float x, float y);
    bool In(vec2 p);
};
