#include "button.h"

void Button::Draw(){
    if(enabled){
        (is_on?on:off)->Draw(position, scale);
    }
}

void Button::Update(vec2 p, vec2 s){
    this->position = p;
    this->scale = s;
}

void Button::On(){
    if(enabled){
        is_on = true;
    }
}
void Button::Off(){
    if(enabled){
        is_on = false;
    }
}

bool Button::In(float x, float y){
    float dx = x - this->position.x, dy = y - this->position.y;
    return (0 <= dx && dx <= this->scale.x && 0 <= dy && dy <= this->scale.y);
}

bool Button::In(vec2 p){
    return In(p.x, p.y);
}