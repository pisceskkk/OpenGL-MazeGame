#include "material.h"

void Material::Activate(){
    GLfloat ambient[]={ambient_r, ambient_g, ambient_b, ambient_a}; 
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient); 
    GLfloat diffuse[]={diffuse_r, diffuse_g, diffuse_b, diffuse_a};  
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse); 
    GLfloat specular[]={specular_r, specular_g, specular_b, specular_a};  
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular); 
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
}