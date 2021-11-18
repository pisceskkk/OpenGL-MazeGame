#pragma once
#include <GL/freeglut.h> 

class Material{ 

private: 

    GLfloat ambient_r; 
    GLfloat ambient_g; 
    GLfloat ambient_b; 
    GLfloat ambient_a; 

    GLfloat diffuse_r; 
    GLfloat diffuse_g; 
    GLfloat diffuse_b; 
    GLfloat diffuse_a; 

    GLfloat specular_r; 
    GLfloat specular_g; 
    GLfloat specular_b; 
    GLfloat specular_a; 

    GLfloat shininess;


public: 

    Material(){memset(this,0,sizeof(Material));}
    Material(GLfloat ar, GLfloat ag, GLfloat ab, GLfloat dr, GLfloat dg, GLfloat db, GLfloat sr, GLfloat sg, GLfloat sb){ 
        ambient_r=ar; ambient_g=ag; ambient_b=ab; 
        diffuse_r=dr; diffuse_g=dg; diffuse_b=db; 
        specular_r=sr; specular_g=sg; specular_b=sb; 
        shininess=0.0;
    } 
    Material(GLfloat ar, GLfloat ag, GLfloat ab, GLfloat dr, GLfloat dg, GLfloat db, GLfloat sr, GLfloat sg, GLfloat sb, GLfloat sh){ 
        ambient_r=ar; ambient_g=ag; ambient_b=ab; ambient_a=1.0;
        diffuse_r=dr; diffuse_g=dg; diffuse_b=db; diffuse_a=1.0;
        specular_r=sr; specular_g=sg; specular_b=sb; specular_a=1.0;
        shininess=sh;
    } 
    Material(GLfloat ar, GLfloat ag, GLfloat ab, GLfloat aa, GLfloat dr, GLfloat dg, GLfloat db, GLfloat da, GLfloat sr, GLfloat sg, GLfloat sb, GLfloat sa, GLfloat sh){ 
        ambient_r=ar; ambient_g=ag; ambient_b=ab; ambient_a=aa;
        diffuse_r=dr; diffuse_g=dg; diffuse_b=db; diffuse_a=da;
        specular_r=sr; specular_g=sg; specular_b=sb; specular_a=sa;
        shininess=sh;
    } 

    void Activate(); 
}; 

const Material kBrass = Material(0.329412, 0.223529, 0.027451, 1.000000, 0.780392, 0.568627, 0.113725, 1.000000, 0.992157, 0.941176, 0.807843, 1.000000, 27.897400);
const Material kBronze = Material(0.212500, 0.127500, 0.054000, 1.000000, 0.714000, 0.428400, 0.181440, 1.000000, 0.393548, 0.271906, 0.166721, 1.000000, 25.600000);
const Material kGolden = Material(0.247250, 0.199500, 0.074500, 1.000000, 0.751640, 0.606480, 0.226480, 1.000000, 0.628281, 0.555802, 0.366065, 1.000000, 51.200001);
const Material kSilver = Material(0.192250, 0.192250, 0.192250, 1.000000, 0.507540, 0.507540, 0.507540, 1.000000, 0.508273, 0.508273, 0.508273, 1.000000, 51.200001);
const Material kObsidian = Material(0.053750, 0.050000, 0.066250, 0.820000, 0.182750, 0.170000, 0.225250, 0.820000, 0.332741, 0.328634, 0.346435, 0.820000, 38.400002);
const Material kBlackPlastic = Material(0.0, 0.0, 0.0, 1.0, 0.1, 0.1, 0.1, 1.0, 0.5, 0.5, 0.5, 1.0, 32.0);