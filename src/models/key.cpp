#include "key.h"
#include <cmath>

const double EPS = 1e-5, PI = acos(-1.0);

static void DrawKey(){
    glPushMatrix();
    glTranslatef(0.0, 0.5, 2.5);
    glRotatef(90, 1.0, 0.0, 0.0);
    glutSolidCylinder(2.5,1.0,100,20);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0, 0.0, 3.0);
    glutSolidCylinder(0.5, 6, 100, 20);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0, 0.0, 8.0);
    glRotatef(90, 1.0, 0.0, 0.0);
    glutSolidCylinder(0.2, 1, 100, 20);
    glPopMatrix();
}

void Key::Draw(){
    glPushMatrix();
    glTranslatef(position.x, position.y, position.z);

	vec3 origin_axis = kXAxis;
    vec3 rot_axis = (normal^origin_axis).normalize();
    if (rot_axis.length() > EPS)
        glRotatef(180*acos(normal*origin_axis)/PI, rot_axis.x, rot_axis.y, rot_axis.z);
    else if (normal*origin_axis < -EPS) 
        glRotatef(180, 1.0, 0.0, 0.0);

    if(use_material)
        material.Activate();
    if(use_texture)
        texture->Activate();
    DrawKey();
    glPopMatrix();
}

void Key::Draw(GLfloat angle){
    glPushMatrix();
    glTranslatef(position.x, position.y, position.z);
    
	vec3 origin_axis = kXAxis;
    vec3 rot_axis = (normal^origin_axis).normalize();
    if (rot_axis.length() > EPS)
        glRotatef(180*acos(normal*origin_axis)/PI, rot_axis.x, rot_axis.y, rot_axis.z);
    else if (normal*origin_axis < -EPS) 
        glRotatef(180, 1.0, 0.0, 0.0);

    glTranslatef(0.0, 0.0, 3.0);
    glRotatef(angle, 0.0, 0.0, 1.0);
    glRotatef(-20, 1.0, 0.0, 0.0);
    glTranslatef(0.0, 0.0, -3.0);

    if(use_material)
        material.Activate();
    if(use_texture)
        texture->Activate();
    
    DrawKey();
    glPopMatrix();

}