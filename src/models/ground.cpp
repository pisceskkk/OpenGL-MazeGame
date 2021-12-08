#include "ground.h"
#include <math.h>
#include <cstdio>

const double EPS = 1e-5;

void Ground::Draw(GLint x_slices, GLint y_slices){
    glPushMatrix();

    if(use_texture){
        glEnable(GL_TEXTURE_2D);
        texture->Activate();
    }
    if(use_material)
        material.Activate();

    glTranslatef(position.x, position.y, position.z);
    vec3 rot_axis = normal^kZAxis;
    if (rot_axis.length() > EPS)
        glRotatef(acos(normal*kZAxis), rot_axis.x, rot_axis.y, rot_axis.z);
    


    glBegin(GL_QUADS);
    glNormal3f(0.0f, 0.0f, 1.0f);
    for (int y = 0; y < y_slices; y++) {
        float y_start = y*10.0f;
        for (int x = 0; x < x_slices; x++) {
            float x_start = x*10.0f;
            glTexCoord2f(0.0f, 0.0f);
            glVertex3f(x_start, y_start, 0.0f);
            glTexCoord2f(1.0f, 0.0f);
            glVertex3f(x_start + 10.0f, y_start, 0.0f);
            glTexCoord2f(1.0f, 1.0f);
            glVertex3f(x_start + 10.0f, y_start + 10.0f, 0.0f);
            glTexCoord2f(0.0f, 1.0f);
            glVertex3f(x_start, y_start + 10.0f, 0.0f);
        }
    }
    glEnd();
    glDisable(GL_TEXTURE_2D);

    glPopMatrix();
}