#include "logo.h"

void Logo::Load(){
    this->texture=Texture(this->name);
    this->texture.Load();
}

void Logo::Draw(vec3 position, vec2 scale){
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_COLOR_MATERIAL);
    this->texture.Activate();
    glPushMatrix();

    glTranslatef(position.x, position.y, position.z);
    glScalef(scale.x, scale.y, 1.0);
    glNormal3f(0.0f, 0.0f, 1.0f);
    glBegin(GL_QUADS);
    {
        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(-0.5f, -0.5f, 0.0f);
        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(0.5f, -0.5f, 0.0f);
        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(0.5f, 0.5f, 0.0f);
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(-0.5f, 0.5f, 0.0f);
    }
    glEnd();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_COLOR_MATERIAL);
}