#include <cstdio>
#include <ctime>
#include <cmath>
#include <string>
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
#include "models/logo.h"
#include "models/button.h"
#include "game/map.h"


void Init();
void InitGame();
void InitCamera();
void InitMap();

void ProcessCamera();

void TurnCameraRight(int value);
void TurnCameraLeft(int value);
void MoveCameraForward(int value);
void MoveCameraBackward(int value);

void ProcessKeys();
void KeyUpSpecial(int key, int x, int y);
void keyUp(unsigned char key, int x, int y);
void KeyboardSpecialKeyInput(int key, int x, int y);
void KeyboardInput(unsigned char key, int x, int y);

void TimerFunc(int value);

void Reshape(int w, int h);
static void RenderSence();
static void Args(int argc, char **argv);


GLenum doubleBuffer;

const GLfloat kInitSpeed=1;
int screenW=800, screenH=600, screenD=1;

struct keypress
{
    bool enabled=false;
    bool W = false;
    bool S = false;
    bool A = false;
    bool D = false;
    bool Z = false;
    bool X = false;
    bool Q = false;
    bool E = false;
    bool R = false;
    bool F = false;
    bool UP = false;
    bool DOWN = false;
    bool LEFT = false;
    bool RIGHT = false;
    bool SHIFT = false;
    bool SPACE = false;
} keysPressed, keysProcessed;

Map map("./assets/maze.txt");
Camera camera;
struct GameState{
    float elapsed_time;
    int key_number;
    bool is_loaded=false;
    bool win=false;
    Logo loading_logo=Logo("./assets/loading.png"),win_logo=Logo("./assets/win.png");
    Logo exit_logo=Logo("./assets/button_exit.png"),exit_down_logo=Logo("./assets/button_exit_down.png");
    Logo reload_logo=Logo("./assets/button_reload.png"),reload_down_logo=Logo("./assets/button_reload_down.png");
    Button exit_button=Button(&exit_logo, &exit_down_logo, vec2(screenW-10-6.5*screenW/100,10),vec2(6.5*screenW/100,4.8*screenH/100));
    Button reload_button=Button(&reload_logo, &reload_down_logo, vec2(10,10), vec2(9.4*screenW/100,4.8*screenH/100));
    void load(){
        loading_logo.Load();
        win_logo.Load();
        exit_logo.Load();
        exit_down_logo.Load();
        reload_logo.Load();
        reload_down_logo.Load();
        is_loaded = true;
    }
}state;


void InitGame(){
    state.elapsed_time = 0;
    state.key_number = 0;
    state.win=false;
    keysPressed.enabled = true;
    keysProcessed.enabled = false;
    if(state.is_loaded == false){
        state.load();
    }
}

void InitCamera(){
    vec3 position = vec3(map.start_pos.x, map.start_pos.y, 15.0);
    vec3 viewDirection = vec3(-1.0, 0.0, 0.0);
    vec3 upVector = vec3(0.0, 0.0, 1.0);
    vec3 rightVector = vec3(0.0, 1.0, 0.0);
    camera = Camera(position, viewDirection, upVector, rightVector, kZeroVec3, kInitSpeed);
}

void InitMap(){
    if(map.is_loaded == false){
        map.Load();
    }
    else {
        map.Init();
    }
}

//camera porcessing
void ProcessCamera()
{
    vec3 viewPoint = camera.position + camera.direction;
    gluLookAt(camera.position.x, camera.position.y, camera.position.z,//eye
        viewPoint.x, viewPoint.y, viewPoint.z,//centre
        camera.up.x, camera.up.y, camera.up.z);
}

void TurnCameraRight(int value){
    if(value <= 0)return;
    camera.RotateY(-1);
    glutTimerFunc(1, TurnCameraRight, value-1);
}
void TurnCameraLeft(int value){
    if(value <= 0)return;
    camera.RotateY(1);
    glutTimerFunc(1, TurnCameraLeft, value-1);
}

void MoveCameraForward(int value){
    if(value <= 0) return;
    camera.Go(0.2);
    glutTimerFunc(1, MoveCameraForward, value-1);
}
void MoveCameraBackward(int value){
    if(value <= 0)return;
    camera.Go(-0.2);
    glutTimerFunc(1, MoveCameraBackward, value-1);
}

//processing key board inputs
void ProcessKeys()
{
    vec3 prePos = camera.position;
    vec3 nxt_pos;
    // functional keys
    if (keysPressed.SPACE){
        return;
    }
    if (keysPressed.R && keysProcessed.R == false){
        keysProcessed.R = true;
        Init();
    }

    if(keysProcessed.enabled == false)
        return;

    // gaming keys
    if (keysPressed.W && keysProcessed.W == false)
    {
        keysProcessed.W = true;
        nxt_pos = camera.position + camera.direction * 10;
        if(map.Check(nxt_pos.x, nxt_pos.y, state.elapsed_time)){
            MoveCameraForward(50);
        }
    }
    if (keysPressed.S && keysProcessed.S == false)
    {
        keysProcessed.S = true;
        nxt_pos = camera.position + camera.direction * (-10);
        if(map.Check(nxt_pos.x, nxt_pos.y, state.elapsed_time)){
            MoveCameraBackward(50);
        }
    }
    if (keysPressed.A && keysProcessed.A == false)
    {
        keysProcessed.A = true;
        TurnCameraLeft(90);
    }
    if (keysPressed.D && keysProcessed.D == false)
    {
        keysProcessed.D = true;
        TurnCameraRight(90);
    }
    if (keysPressed.E && keysProcessed.E == false){
        keysProcessed.E = true;
        nxt_pos = camera.position + camera.direction * 10;
        char nxt_state = map.get_state(nxt_pos.x, nxt_pos.y);
        if(nxt_state == '-' || nxt_state == '|'){
            if(state.key_number > 0){
                state.key_number--;
                map.OpenDoor(nxt_pos.x, nxt_pos.y, state.elapsed_time);
            }
            else {

            }
        }
    }
    if (keysPressed.F && keysProcessed.F == false){
        keysProcessed.F = true;
        nxt_pos = camera.position;
        char map_state = map.get_state(nxt_pos.x, nxt_pos.y);
        if(map_state == 'k'){
            state.key_number += map.FetchKey(nxt_pos.x, nxt_pos.y);
        }
        else if (map_state == 'e'){
            state.win = true;
        }
    }
}

void KeyUpSpecial(int key, int x, int y)
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
        keysProcessed.W = false;
        break;
    case 's': case 'S':
        keysPressed.S = false;
        keysProcessed.S = false;
        break;
    case 'a': case 'A':
        keysPressed.A = false;
        keysProcessed.A = false;
        break;
    case 'd': case 'D':
        keysPressed.D = false;
        keysProcessed.D = false;
        break;
    case 'z': case 'Z':
        keysPressed.Z = false;
        keysProcessed.Z = false;
        break;
    case 'x': case 'X':
        keysPressed.X = false;
        keysProcessed.X = false;
        break;
    case 'q': case 'Q':
        keysPressed.Q = false;
        keysProcessed.Q = false;
        break;
    case 'e': case 'E':
        keysPressed.E = false;
        keysProcessed.E = false;
        break;
    case 'f': case 'F':
        keysPressed.F = false;
        keysProcessed.F = false;
        break;
    case 'r': case 'R':
        keysPressed.R = false;
        keysProcessed.R = false;
        break;
    case ' ':
        keysPressed.SPACE = false;
        keysProcessed.SPACE = false;
        break;
    }
}

void KeyboardSpecialKeyInput(int key, int x, int y)
{
    switch (key) {
    case GLUT_KEY_UP: keysPressed.UP = true; break;
    case GLUT_KEY_DOWN: keysPressed.DOWN = true; break;
    case GLUT_KEY_LEFT: keysPressed.LEFT = true; break;
    case GLUT_KEY_RIGHT: keysPressed.RIGHT = true; break;
    case GLUT_KEY_SHIFT_L: keysPressed.SHIFT = true; break;
    }
}

void KeyboardInput(unsigned char key, int x, int y)
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
    case 'f': case 'F':
        keysPressed.F = true;
        break;
    case 'r': case 'R':
        keysPressed.R = true;
        break;
    case ' ':
        keysPressed.SPACE = true;
        InitCamera();
        break;
    case 27: // ECS
        exit(0);
        break;
    }
    
}

void TimerFunc(int value)
{
    state.elapsed_time += 0.25;
    ProcessKeys();
    glutSwapBuffers();
    glutPostRedisplay();
    glutTimerFunc(25, TimerFunc, 1);
}

void Reshape(int w, int h)
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

    state.exit_button.Update(vec2(screenW-10-6.5*screenW/100,10),vec2(6.5*screenW/100,4.8*screenH/100));
    state.reload_button.Update(vec2(10,10), vec2(9.4*screenW/100,4.8*screenH/100));
}

static void RenderSence()
{
    glClear(GL_COLOR_BUFFER_BIT  | GL_DEPTH_BUFFER_BIT); 
    glEnable(GL_DEPTH_TEST);     

    // Draw on screen
    glMatrixMode(GL_PROJECTION);
    {
        glLoadIdentity();
        gluOrtho2D(0, screenW, screenH, 0);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        // Loading
        if(state.elapsed_time < 5){
            keysProcessed.enabled = false;
            state.loading_logo.Draw(vec2(0,screenH/2-screenW/5), vec2(screenW,screenW/2.5));
        }
        else {
            keysProcessed.enabled = true;
        }
        if(state.win){
            state.win_logo.Draw(vec2(screenW/4, screenH/4), vec2(screenW/2, screenH/2));
            keysProcessed.enabled = false;
        }
        state.exit_button.Draw();
        state.reload_button.Draw();
    }

    // Draw in space
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(55.0f, screenW/screenH, 1.0, 100000.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    ProcessCamera();

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

    map.Draw(state.elapsed_time);

    if (doubleBuffer) {
        glutSwapBuffers();
    } else {
        glFlush();
    }
}


void mouse_hit(int mbutton, int mstate, int x, int y){
    //鼠标操作基本结构
    switch (mbutton)
    {
    case GLUT_LEFT_BUTTON:
        if (mstate == GLUT_DOWN)
        {
            if(state.exit_button.In(x,y)){
                state.exit_button.On();
            }
            if(state.reload_button.In(x,y)){
                state.reload_button.On();
            }
        }
        else if (mstate == GLUT_UP){
            if(state.exit_button.In(x,y)){
                state.exit_button.Off();
                exit(0);
            }
            if(state.reload_button.In(x,y)){
                state.reload_button.Off();
                Init();
            }
        }
        break;
    case GLUT_RIGHT_BUTTON:
    default:
        break;
    }
}

void mouse_move(int x, int y)
{
    glutSetWindowTitle((std::to_string(x) + " " + std::to_string(y)).c_str());
    if(state.exit_button.In(x,y)){
        state.exit_button.On();
    }
    else {
        state.exit_button.Off();
    }
    if(state.reload_button.In(x,y)){
        state.reload_button.On();
    }
    else {
        state.reload_button.Off();
    }
}


static void Args(int argc, char **argv)
{
    doubleBuffer = GL_FALSE;
}

void Init(){
    glClearColor(0.3, 0.3, 0.3, 0.0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    InitMap();
    InitCamera();
    InitGame();
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

    glutSpecialFunc(KeyboardSpecialKeyInput);
    glutSpecialUpFunc(KeyUpSpecial);
    glutKeyboardFunc(KeyboardInput);
    glutKeyboardUpFunc(keyUp);
    glutReshapeFunc(Reshape);
    glutDisplayFunc(RenderSence);
    glutTimerFunc(25, TimerFunc, 1);
    glutMouseFunc(mouse_hit);
    glutMotionFunc(mouse_move);
    glutMainLoop();
}