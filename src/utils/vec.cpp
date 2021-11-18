#include <math.h>
#include "vec.h"


vec3 vec3::operator+(const vec3 o) const {
    return vec3(this->x+o.x, y+o.y, z+o.z);
}
vec3 vec3::operator-(const vec3 o) const {
    return vec3(x-o.x, y-o.y, z-o.z);
}
vec3 vec3::operator*(const float k) const {
    return vec3(k*x, k*y, k*z);
}
vec3 vec3::operator/(const float k) const {
    return vec3(k/x, k/y, k/z);
}
float vec3::operator*(const vec3 o) const {
    return x*o.x + y*o.y + z*o.z;
}
vec3 vec3::operator^(const vec3 o) const {
    return vec3(y*o.z-z*o.y, z*o.x-x*o.z, x*o.y-y*o.x);
}
float vec3::length() const {
    return sqrt(x*x+y*y+z*z);
}
vec3 vec3::normalize() const {
    float len = this->length();
    return vec3(this->x/len, this->y/len, this->z/len);
}

vec2 vec2::operator+(const vec2 o) const {
    return vec2(this->x+o.x, y+o.y);
}
vec2 vec2::operator-(const vec2 o) const {
    return vec2(x-o.x, y-o.y);
}
vec2 vec2::operator*(const float k) const {
    return vec2(k*x, k*y);
}
vec2 vec2::operator/(const float k) const {
    return vec2(k/x, k/y);
}
float vec2::operator*(const vec2 o) const {
    return x*o.x + y*o.y;
}
float vec2::operator^(const vec2 o) const {
    return x*o.y-y*o.x;
}
float vec2::length() const {
    return sqrt(x*x+y*y);
}
vec2 vec2::normalize() const {
    float len = this->length();
    return vec2(this->x/len, this->y/len);
}