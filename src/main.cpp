#include <cstdio>
#include <ctime>
#include <cmath>
#if defined(_WIN32) || defined(WIN32)
#include <windows.h> 
#endif
#include <GL/freeglut.h>
#include "utils/camera.h"
#include "utils/tools.h"
#include "utils/material.h"
#include "utils/texture.h"
#include "models/key.h"
#include "models/ground.h"
#include "models/door.h"
#include "models/wall.h"
#include "models/star.h"


GLenum doubleBuffer;

const GLfloat kInitSpeed=1;
GLfloat elapsed_time = 0;
int screenW=800, screenH=600;
struct keypress
{
    bool W = false;
    bool S = false;
    bool A = false;
    bool D = false;
    bool Z = false;
    bool X = false;
    bool Q = false;
    bool E = false;
    bool UP = false;
    bool DOWN = false;
    bool LEFT = false;
    bool RIGHT = false;
    bool SHIFT = false;
    bool SPACE = false;
} keysPressed;

Texture kPebble("./assets/pebble.jpg");
Texture kBrick("./assets/brick.jpg");

Key test_key(vec3(-5.0, 0.0, 0.0), kXAxis, kGolden);
Key test_key2(vec3(-10.0, 0.0, 0.0), kXAxis, kBrass);
Door test_door(kZeroVec3, kXAxis, kBrass);
Wall test_wall1(vec3(0.0,  10.0, 0.0), kXAxis, &kBrick);
Wall test_wall2(vec3(0.0, -10.0, 0.0), kXAxis, &kBrick);
Ground ground(kZeroVec3, kZAxis, &kPebble);
Star test_star(vec3(5.0, 0.0, 0.0), kXAxis, kSilver);

Camera camera;
void InitCamera(){
    vec3 position = vec3(40.0, 0.0, 15.0);
    vec3 viewDirection = vec3(-1.0, 0.0, 0.0);
    vec3 upVector = vec3(0.0, 0.0, 1.0);
    vec3 rightVector = vec3(0.0, 1.0, 0.0);
    camera = Camera(position, viewDirection, upVector, rightVector, kZeroVec3, kInitSpeed);
}


//camera porcessing
void processCamera()
{
    vec3 viewPoint = camera.position + camera.direction;
    gluLookAt(camera.position.x, camera.position.y, camera.position.z,//eye
        viewPoint.x, viewPoint.y, viewPoint.z,//centre
        camera.up.x, camera.up.y, camera.up.z);
}

//draw Camera Info on screen
void CameraInfo()
{
    DrawText("Camera Position X : " + std::to_string(camera.position.x), GLUT_BITMAP_HELVETICA_12, vec3{ 1.0, 0.0, 0.0 }, vec2(50, 100));
    DrawText("Camera Position Y : " + std::to_string(camera.position.y), GLUT_BITMAP_HELVETICA_12, vec3{ 1.0, 1.0, 0.0 }, vec2(50, 125));
    DrawText("Camera Position Z : " + std::to_string(camera.position.z), GLUT_BITMAP_HELVETICA_12, vec3{ 0.0, 1.0, 1.0 }, vec2(50, 150));
    DrawText("Rotation X : " + std::to_string(camera.rotation.x), GLUT_BITMAP_HELVETICA_12, vec3{ 1.0, 1.0, 1.0 }, vec2(50, 200));
    DrawText("Rotation Y : " + std::to_string(camera.rotation.y), GLUT_BITMAP_HELVETICA_12, vec3{ 1.0, 1.0, 1.0 }, vec2(50, 225));
    DrawText("Rotation Z : " + std::to_string(camera.rotation.z), GLUT_BITMAP_HELVETICA_12, vec3{ 1.0, 1.0, 1.0 }, vec2(50, 250));
    glutSetWindowTitle((std::to_string(camera.direction.x) + std::to_string(camera.direction.y) + std::to_string(camera.direction.z) +
                        std::to_string(camera.right.x) + std::to_string(camera.right.y) + std::to_string(camera.right.z) +
                        std::to_string(camera.up.x) + std::to_string(camera.up.y) + std::to_string(camera.up.z)
                        ).c_str());
}

//processing key board inputs
void processKeys()
{
    vec3 prePos = camera.position;
    if (keysPressed.SPACE){
        InitCamera();
        return;
    }
    if (keysPressed.W)
    {
        camera.MoveForward();
    }
    if (keysPressed.S)
    {
        camera.MoveBackward();
    }
    if (keysPressed.A)
    {
        camera.MoveLeft();
    }
    if (keysPressed.D)
    {
        camera.MoveRight();
    }
    if (keysPressed.Z)
    {
        camera.RotateY(1.0);
    }
    if (keysPressed.X)
    {
        camera.RotateY(-1.0);
    }
    if (keysPressed.UP)
    {
        camera.MoveUp();
    }
    if (keysPressed.DOWN)
    {
        camera.MoveDown();
    }
    if (keysPressed.LEFT)
    {
        camera.RotateZ(1.0);
    }
    if (keysPressed.RIGHT)
    {
        camera.RotateZ(-1.0);
    }
    if (keysPressed.Q) {
        camera.RotateX(1.0);
    }
    if (keysPressed.E) {
        camera.RotateX(-1.0);
    }
}

void keyUpSpecial(int key, int x, int y)
{
    switch (key) {
    case GLUT_KEY_UP: keysPressed.UP = false; break;
    case GLUT_KEY_DOWN: keysPressed.DOWN = false; break;
    case GLUT_KEY_LEFT: keysPressed.LEFT = false; break;
    case GLUT_KEY_RIGHT: keysPressed.RIGHT = false; break;
    case GLUT_KEY_SHIFT_L: keysPressed.SHIFT = false; break;
    }
}

void keyUp(unsigned char key, int x, int y)
{
    switch (key) {
    case 'w': case 'W':
        keysPressed.W = false;
        break;
    case 's': case 'S':
        keysPressed.S = false;
        break;
    case 'a': case 'A':
        keysPressed.A = false;
        break;
    case 'd': case 'D':
        keysPressed.D = false;
        break;
    case 'z': case 'Z':
        keysPressed.Z = false;
        break;
    case 'x': case 'X':
        keysPressed.X = false;
        break;
    case 'q': case 'Q':
        keysPressed.Q = false;
        break;
    case 'e': case 'E':
        keysPressed.E = false;
        break;
    case ' ':
        keysPressed.SPACE = false;
        break;
    }
}

void keyboardSpecialKeyInput(int key, int x, int y)
{
    switch (key) {
    case GLUT_KEY_UP: keysPressed.UP = true; break;
    case GLUT_KEY_DOWN: keysPressed.DOWN = true; break;
    case GLUT_KEY_LEFT: keysPressed.LEFT = true; break;
    case GLUT_KEY_RIGHT: keysPressed.RIGHT = true; break;
    case GLUT_KEY_SHIFT_L: keysPressed.SHIFT = true; break;
    }
}

void keyboardInput(unsigned char key, int x, int y)
{
    switch (key) {
    case 'w': case 'W':
        keysPressed.W = true;
        break;
    case 's': case 'S':
        keysPressed.S = true;
        break;
    case 'a': case 'A':
        keysPressed.A = true;
        break;
    case 'd': case 'D':
        keysPressed.D = true;
        break;
    case 'z': case 'Z':
        keysPressed.Z = true;
        break;
    case 'x': case 'X':
        keysPressed.X = true;
        break;
    case 'q': case 'Q':
        keysPressed.Q = true;
        break;
    case 'e': case 'E':
        keysPressed.E = true;
        break;
    case ' ':
        keysPressed.SPACE = true;
        break;
    case 27: // ECS
        exit(0);
        break;
    }
    
}

void TimerFunc(int value)
{
    //timer function
	elapsed_time += 0.25;
    processKeys();
    glutSwapBuffers();
    glutPostRedisplay();
    glutTimerFunc(25, TimerFunc, 1);
}

void reshape(int w, int h)
{
    GLfloat fAspect;

    if (h == 0) h = 1;

    glViewport(0, 0, w, h);
    screenW = w; screenH = h;
    fAspect = (GLfloat)w / (GLfloat)h;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(55.0f, fAspect, 1.0, 100000.0);
    glMatrixMode(GL_MODELVIEW);
    gluLookAt(0.00, 0.00, 0.0,
        0.00, 0.00, -1.00,
        0.00, 1.00, 0.00);
}

static void RenderSence(void)
{
    glClear(GL_COLOR_BUFFER_BIT  | GL_DEPTH_BUFFER_BIT); 
    glEnable(GL_DEPTH_TEST);     
    glLoadIdentity();
    processCamera();
    // CameraInfo();

    {
        GLfloat sun_light_position[][4] = {{100.0f, 100.0f, 100.0f, 1.0f},{-100.0f, -100.0f, 100.0f, 1.0f}};
        GLfloat sun_light_ambient[]  = {0.0f, 0.0f, 0.0f, 1.0f};     
        GLfloat sun_light_diffuse[]  = {1.0f, 1.0f, 1.0f, 1.0f};     
        GLfloat sun_light_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};      
        glLightfv(GL_LIGHT0, GL_POSITION, sun_light_position[0]);     
        glLightfv(GL_LIGHT0, GL_AMBIENT,  sun_light_ambient);     
        glLightfv(GL_LIGHT0, GL_DIFFUSE,  sun_light_diffuse);     
        glLightfv(GL_LIGHT0, GL_SPECULAR, sun_light_specular);      
        glEnable(GL_LIGHT0);     
        glLightfv(GL_LIGHT1, GL_POSITION, sun_light_position[1]);     
        glLightfv(GL_LIGHT1, GL_AMBIENT,  sun_light_ambient);     
        glLightfv(GL_LIGHT1, GL_DIFFUSE,  sun_light_diffuse);     
        glLightfv(GL_LIGHT1, GL_SPECULAR, sun_light_specular);      
        glEnable(GL_LIGHT1);     
        glEnable(GL_LIGHTING);     
    } 

    test_key.Draw(elapsed_time*10);
    test_key2.Draw(elapsed_time*10);
    test_star.Draw(elapsed_time*10);
    test_door.Draw(elapsed_time);
    test_wall1.Draw();
    test_wall2.Draw();
    ground.Draw(10, 10);

    if (doubleBuffer) {
    glutSwapBuffers();
    } else {
    glFlush();
    }
}


static void Args(int argc, char **argv)
{
    GLint i;

    doubleBuffer = GL_FALSE;

    for (i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-sb") == 0) {
            doubleBuffer = GL_FALSE;
        } else if (strcmp(argv[i], "-db") == 0) {
            doubleBuffer = GL_TRUE;
        }
    }
}

void Init(){
    glClearColor(0.3, 0.3, 0.3, 0.0);
    InitCamera();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
    kPebble.Load();
    kBrick.Load();
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    test_door.open(5, 2);
}

int main(int argc, char **argv)
{
    GLenum type;

    glutInit(&argc, argv);
    Args(argc, argv);

    type = GLUT_RGB;
    type |= (doubleBuffer) ? GLUT_DOUBLE : GLUT_SINGLE;
    glutInitDisplayMode(type);
    glutInitWindowSize(screenW, screenH);
    glutCreateWindow("Maze Game");

    Init();

    glutSpecialFunc(keyboardSpecialKeyInput);
    glutSpecialUpFunc(keyUpSpecial);
    glutKeyboardFunc(keyboardInput);
    glutKeyboardUpFunc(keyUp);
    glutReshapeFunc(reshape);
    glutDisplayFunc(RenderSence);
	glutTimerFunc(25, TimerFunc, 1);
    glutMainLoop();
}