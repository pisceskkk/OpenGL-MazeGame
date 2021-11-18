#include <cmath>
#include "camera.h"

const double PI = acos(-1.0);


float ResetAngle(float angle)
{
    while (angle > 360) {
        angle -= 360;
    }
    while (angle < 0) {
        angle += 360;
    }
    return angle;
}


void Camera::Move(vec3 direction)
{
    this->position = this->position+ direction;
};

void Camera::MoveForward()
{
    this->position = this->position + (this->direction * this->speed);
};

void Camera::MoveBackward()
{
    this->position = this->position + (this->direction * (-this->speed));
};

void Camera::MoveRight()
{
    this->position = this->position + (this->right * this->speed);
};

void Camera::MoveLeft()
{
    this->position = this->position + (this->right * (-this->speed));
};

void Camera::MoveUp()
{
    this->position = this->position + (this->up * this->speed);
};

void Camera::MoveDown()
{
    this->position = this->position + (this->up * (-this->speed));
};

void Camera::RotateX(float angle)
{

    this->rotation.x = ResetAngle(this->rotation.x + angle);

    //Rotate viewdir around the right vector:
    this->direction = ((this->direction * cos(angle * (PI/180.0))) + (this->up * sin(angle * (PI / 180.0)))).normalize();

    //now compute the new UpVector (by cross product)
    this->up= (this->direction ^ this->right) * (-1);
};

void Camera::RotateY(float angle)
{
    this->rotation.y  = ResetAngle(this->rotation.y + angle);

    //Rotate viewdir around the up vector:
    this->direction = ((this->direction * cos(angle * (PI / 180.0))) - (this->right * sin(angle * (PI / 180.0)))).normalize();

    //now compute the new RightVector (by cross product)
    this->right = this->direction ^ this->up;

};

void Camera::RotateZ(float angle)
{
    this->rotation.z  = ResetAngle(this->rotation.z + angle);

    //Rotate viewdir around the right vector:
    this->right = ((this->right * cos(angle * (PI / 180.0))) + (this->up * sin(angle * (PI / 180.0)))).normalize();

    //now compute the new UpVector (by cross product)
    this->up = (this->direction ^ this->right) * (-1);
};