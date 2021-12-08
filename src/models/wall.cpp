#include "wall.h"
#include "../utils/tools.h"
#include <cmath>
const double EPS = 1e-5, PI = acos(-1.0);

void Wall::Draw(){
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
    if(use_texture){
        glEnable(GL_TEXTURE_2D);
        texture->Activate();
    }
    glScalef(10,10,23);
    glTranslatef(0, 0, 0.5);
    DrawUnitCube(1);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}