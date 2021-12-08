#pragma once
#include <string>
#include <cstring>
#include "../utils/vec.h"
#include "../models/ground.h"
#include "../models/wall.h"
#include "../models/door.h"
#include "../models/key.h"
#include "../models/star.h"

class Map{
private:
    char* name;
    char* map;
    int width, height;
    char* state;
    Model** models;
    int key_num;
    Texture pebble=Texture("./assets/pebble.jpg");
    Texture brick=Texture("./assets/brick.jpg");
    int encode(vec2 pos);
    int encode(int x,int y);
public:
    bool is_loaded=false;
    vec2 start_pos;
    vec2 end_pos;
    Map(){}
    Map(const char* file_dir){
        name = (char *)malloc((strlen(file_dir) + 1) * sizeof(char));
        memcpy(name, file_dir, strlen(file_dir)+1);
    }
    /*
    maze file format:
    height width
    width*height char matrix
    where '#': wall,
          '|' and '-': door, 
          'k': key, 
          's': start position,
          'e': end position.
     */
    void Load(const char* file_dir);
    void Load();
    void Init();
    void Draw(float time);
    bool Check(float x, float y, float time);
    bool FetchKey(vec2 pos);
    bool FetchKey(int x, int y);
    bool OpenDoor(vec2 pos, float time);
    bool OpenDoor(int x, int y, float time);
    char get_state(vec2 pos);
    char get_state(int x, int y);
};