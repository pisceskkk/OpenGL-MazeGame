#pragma once

class vec3
{
public:
    float x;
    float y;
    float z;

    vec3():x(0.0f), y(0.0f), z(0.0f){}
    vec3(float X, float Y, float Z):x(X), y(Y), z(Z){}

    vec3 operator+(const vec3 o)const;
    vec3 operator-(const vec3 o)const;
    float operator*(const vec3 o)const;
    vec3 operator^(const vec3 o)const;

    vec3 operator*(const float k)const;
    vec3 operator/(const float k)const;
    
    float length()const;
    vec3 normalize()const;
};

const vec3 kZeroVec3 = vec3(0.0f, 0.0f, 0.0f),
    kXAxis = vec3(1.0f, 0.0f, 0.0f),
    kYAxis = vec3(0.0f, 1.0f, 0.0f),
    kZAxis = vec3(0.0f, 0.0f, 1.0f);

class vec2
{
public:
    float x;
    float y;

    vec2():x(0.0f), y(0.0f){}
    vec2(const float X, const float Y):x(X), y(Y){}

    vec2 operator+(const vec2 o)const;
    vec2 operator-(const vec2 o)const;
    float operator*(const vec2 o)const;
    float operator^(const vec2 o)const;

    vec2 operator*(const float k)const;
    vec2 operator/(const float k)const;

    float length()const;
    vec2 normalize()const;
};

const vec2 kZeroVec2 = vec2(0.0f, 0.0f);