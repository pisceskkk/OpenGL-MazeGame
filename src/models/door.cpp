#include "door.h"
#include <cmath>

inline GLfloat max(GLfloat x, GLfloat y){ return x>y?x:y; }
inline GLfloat min(GLfloat x, GLfloat y){ return x<y?x:y; }

const double EPS = 1e-5, PI = acos(-1.0);

static void DrawDoor(Material material){
    glPushMatrix();

    // main
    glPushMatrix();
    glScalef(3,10,20);
    glTranslatef(0.0, 0.5, 0.5);
    glutSolidCube(1);
    glPopMatrix();

    // handle
    glPushMatrix();
    glTranslatef(1.5,8.0, 8.0);
    glRotatef(90,0, 1, 0);
    glutSolidCone(0.25, 0.5, 100, 100);
        glPushMatrix();
        glTranslatef(0.0, 0.0, 0.5);
        glScalef(1.0, 1.0, 0.5);
        glutSolidSphere(0.5, 100, 100);
        glPopMatrix();
    glPopMatrix();

    // key hole
    glPushMatrix();
    glTranslatef(1.55, 8.3, 7.0);
    glEnable(GL_COLOR_MATERIAL);
    DrawCircle3D(kZeroVec3, kXAxis, 0.25, kZeroVec3, 100);
    glBegin(GL_TRIANGLES);
    glVertex3f(0.0,  0.0,  0.0);
    glVertex3f(0.0, -0.2, -0.75);
    glVertex3f(0.0,  0.2, -0.75);
    glEnd();
    glDisable(GL_COLOR_MATERIAL);
    glPopMatrix();
    material.Activate();

    // decoration
    /* 
    glPushMatrix();
    glTranslatef(0.5, 5.0, 15.0);
    glutSolidSphere(2, 100, 100);
        glPushMatrix();
        glTranslatef(1.5, 0.0, -1.0);
        glRotatef(90, 0.0, 1.0, 0.0);
        glutSolidTorus(0.2, 1.0, 100, 100);
        glPopMatrix();
    glPopMatrix();
     */

    glPopMatrix();
}

void Door::Draw(){
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
    DrawDoor(this->material);
    glPopMatrix();
}

void Door::Draw(float time){
    glPushMatrix();
    GLfloat distance = 0;
    if(this->is_open == 1){
        distance = max(0,min(7.5, (time-this->start_time)*speed));
    }
    glTranslatef(position.x, position.y-distance, position.z);

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
    DrawDoor(this->material);
    glPopMatrix();
}

void Door::open(GLfloat start_time, GLfloat speed){
    this->speed = speed;
    this->start_time = start_time;
    this->is_open = 1;
}