#include "tools.h"
#include <cmath>
const double PI = acos(-1.0), EPS = 1e-5;

void DrawText(std::string text, void* font, vec3 color, vec2 position)
{
    glColor3f(color.x, color.y, color.z);
    glPushMatrix();
    glRasterPos2i(position.x, position.y);
    for (std::string::iterator i = text.begin(); i != text.end(); ++i)
    {
        char c = *i;
        glutBitmapCharacter(font, c);
    }
    glPopMatrix();
}

void DrawCircle3D(vec3 center, vec3 normal, GLfloat radius, vec3 color, GLint slices){
    glPushMatrix();
    glTranslatef(center.x, center.y, center.z);
    vec3 origin_axis = kXAxis;
    vec3 rot_axis = (normal^origin_axis).normalize();
    if (rot_axis.length() > EPS)
        glRotatef(180*acos(normal*origin_axis)/PI, rot_axis.x, rot_axis.y, rot_axis.z);
    else if (normal*origin_axis < -EPS) 
        glRotatef(180, 1.0, 0.0, 0.0);
    glScalef(1.0, radius, radius);
    glColor3f(color.x, color.y, color.z);
    glBegin(GL_POLYGON);
    for(int i=0; i<slices; i++){
        float y_tmp = sin(i*2*PI/slices);
        float z_tmp = cos(i*2*PI/slices);
        glVertex3f(0, y_tmp, z_tmp);
    }
    glEnd();
    glPopMatrix();
}

void DrawUnitCube(GLboolean use_texture){
    static const GLfloat n[6][3] =
    {
        {-1.0, 0.0, 0.0},
        {0.0, 1.0, 0.0},
        {1.0, 0.0, 0.0},
        {0.0, -1.0, 0.0},
        {0.0, 0.0, 1.0},
        {0.0, 0.0, -1.0}
    };
    static const GLint faces[6][4] =
    {
        {0, 1, 2, 3},
        {3, 2, 6, 7},
        {7, 6, 5, 4},
        {4, 5, 1, 0},
        {5, 6, 2, 1},
        {7, 4, 0, 3}
    };
    GLfloat v[8][3];
    GLint i;

    v[0][0] = v[1][0] = v[2][0] = v[3][0] = -1.0 / 2;
    v[4][0] = v[5][0] = v[6][0] = v[7][0] = 1.0 / 2;
    v[0][1] = v[1][1] = v[4][1] = v[5][1] = -1.0 / 2;
    v[2][1] = v[3][1] = v[6][1] = v[7][1] = 1.0 / 2;
    v[0][2] = v[3][2] = v[4][2] = v[7][2] = -1.0 / 2;
    v[1][2] = v[2][2] = v[5][2] = v[6][2] = 1.0 / 2;

    for (i = 5; i >= 0; i--) {
        glBegin(GL_QUADS);
        glNormal3fv(&n[i][0]);
        if(use_texture)glTexCoord2f(0,0);
        glVertex3fv(&v[faces[i][0]][0]);
        if(use_texture)glTexCoord2f(0,1);
        glVertex3fv(&v[faces[i][1]][0]);
        if(use_texture)glTexCoord2f(1,1);
        glVertex3fv(&v[faces[i][2]][0]);
        if(use_texture)glTexCoord2f(1,0);
        glVertex3fv(&v[faces[i][3]][0]);
        glEnd();
    }
}