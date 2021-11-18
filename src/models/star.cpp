#include "star.h"
#include <cmath>

const double EPS = 1e-5, PI = acos(-1.0);

void DrawStar(){
    static GLfloat vert1[][3] = {{0, sin(0*0.4*PI), cos(0*0.4*PI)},
                                {0, sin(1*0.4*PI), cos(1*0.4*PI)},
                                {0, sin(2*0.4*PI), cos(2*0.4*PI)},
                                {0, sin(3*0.4*PI), cos(3*0.4*PI)},
                                {0, sin(4*0.4*PI), cos(4*0.4*PI)}};
    static GLfloat _r2 = 2*(vert1[3][1]*(vert1[1][2]-vert1[3][2])/(vert1[1][1]-vert1[3][1])-vert1[3][2]);
    static GLfloat vert2[][3] = {{0, _r2*sin(3*0.4*PI), _r2*cos(3*0.4*PI)},
                                {0, _r2*sin(4*0.4*PI), _r2*cos(4*0.4*PI)},
                                {0, _r2*sin(0*0.4*PI), _r2*cos(0*0.4*PI)},
                                {0, _r2*sin(1*0.4*PI), _r2*cos(1*0.4*PI)},
                                {0, _r2*sin(2*0.4*PI), _r2*cos(2*0.4*PI)}};
    static GLfloat vert3[][3] = {{0.3, 0.0, 0.0}, {-0.3, 0.0, 0.0}};
    glPushMatrix();
    glTranslatef(0.0, 0.0, 5.0);
    glScalef(4.0, 4.0, 4.0);
    vec3 norm;
    glBegin(GL_TRIANGLES);
    for (int i = 0; i < 5; i++){
        /*
        //                 ^    <-- v1[i]
        //               / * \
        //              /  *  \
        // v2[i-1] --> *. 0*1 .*  <-- v2[i]
        //               - * -
        //                 v3
         */
        // front 0
        norm = vec3(vert1[i][0]-vert2[(i+4)%5][0], vert1[i][1]-vert2[(i+4)%5][1], vert1[i][2]-vert2[(i+4)%5][2])^vec3(vert1[i][0]-vert3[0][0], vert1[i][1]-vert3[0][1], vert1[i][2]-vert3[0][2]);
        glNormal3f(norm.x, norm.y, norm.z);
        glVertex3fv(vert1[i]);
        glVertex3fv(vert2[(i+4)%5]);
        glVertex3fv(vert3[0]);
        // front 1
        norm = vec3(vert1[i][0]-vert2[i][0], vert1[i][1]-vert2[i][1], vert1[i][2]-vert2[i][2])^vec3(vert1[i][0]-vert3[0][0], vert1[i][1]-vert3[0][1], vert1[i][2]-vert3[0][2]);
        glNormal3f(norm.x, norm.y, norm.z);
        glVertex3fv(vert1[i]);
        glVertex3fv(vert2[i]);
        glVertex3fv(vert3[0]);
        // back 0
        norm = vec3(vert1[i][0]-vert2[(i+4)%5][0], vert1[i][1]-vert2[(i+4)%5][1], vert1[i][2]-vert2[(i+4)%5][2])^vec3(vert1[i][0]-vert3[1][0], vert1[i][1]-vert3[1][1], vert1[i][2]-vert3[1][2]);
        glNormal3f(norm.x, norm.y, norm.z);
        glVertex3fv(vert1[i]);
        glVertex3fv(vert2[(i+4)%5]);
        glVertex3fv(vert3[1]);
        // back 1
        norm = vec3(vert1[i][0]-vert2[i][0], vert1[i][1]-vert2[i][1], vert1[i][2]-vert2[i][2])^vec3(vert1[i][0]-vert3[1][0], vert1[i][1]-vert3[1][1], vert1[i][2]-vert3[1][2]);
        glNormal3f(norm.x, norm.y, norm.z);
        glVertex3fv(vert1[i]);
        glVertex3fv(vert2[i]);
        glVertex3fv(vert3[1]);
    }
    glEnd();
    glPopMatrix();
}

void Star::Draw(){
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
    DrawStar();
    glPopMatrix();
}

void Star::Draw(GLfloat angle){
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
    glTranslatef(0.0, 0.0, -3.0);

    if(use_material)
        material.Activate();
    if(use_texture)
        texture->Activate();
    DrawStar();
    glPopMatrix();

}