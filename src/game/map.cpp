#include "map.h"

static FILE* my_log = fopen("./bin/log", "a");

void Map::Load(const char* file_dir){
    name = (char *)malloc((strlen(file_dir) + 1) * sizeof(char));
    memcpy(name, file_dir, strlen(file_dir)+1);
    this->Load();
}

void Map::Load(){
    this->is_loaded = false;
    FILE* f=fopen(name, "r");
    if(!f){
        fprintf(my_log, "Error: Could not open file %s\n", name);
        return;
    }
    fscanf(f, "%d %d", &width, &height);
    fprintf(my_log, "%d %d\n", width, height);
    map = (char *)malloc(sizeof(char) * width * height ); 
    for(int x=0; x<height; x++){
        fscanf(f, "\n");
        for(int y=0; y<width; y++){
            int code = encode(x, y);
            fscanf(f, "%c", &map[code]);
            fprintf(my_log, "%d %d %c\n", x, y, map[code]);
        }
    }
    fclose(f);
    fprintf(my_log, "Load successfully!\n");
    brick.Load();
    pebble.Load();
    Init();
    this->is_loaded = true;
}

void Map::Init(){
    if (state)
        free(state);
    if (models){
        for(int x=0; x < height; x++) {
            for (int y=0; y < width; y++) {
                int code = encode(x, y);
                if (models[code])
                    free(models[code]);
            }
        }
        free(models);
    }
    state = (char *)malloc(sizeof(char) * width * height);
    memcpy(state, map, sizeof(char) * width * height);
    models = (Model **)malloc(sizeof(Model *) * width * height);
    for(int x=0; x < height; x++) {
        for (int y=0; y < width; y++) {
            vec3 pos(x*10+5, y*10+5, 0);
            int code = encode(x, y);
            if (state[code] == '#') {
                models[code] = (Model *)((Wall *)malloc(sizeof(Wall)))->Init(pos, kXAxis, &brick);
            }
            else if (state[code] == '|') {
                models[code] = (Model *)((Door *)malloc(sizeof(Door)))->Init(pos, kYAxis, kBrass);
            }
            else if (state[code] == '-') {
                models[code] = (Model *)((Door *)malloc(sizeof(Door)))->Init(pos, kXAxis, kBrass);
            }
            else if (state[code] == 'k') {
                models[code] = (Model *)((Key *)malloc(sizeof(Key)))->Init(pos+vec3(0,0,5), kXAxis, kBrass);
            }
            else if (state[code] == 's') {
                start_pos = vec2(x*10+5,y*10+5);
            }
            else if (state[code] == 'e') {
                end_pos = vec2(x*10+5,y*10+5);
                models[code] = (Model *)((Star *)malloc(sizeof(Star)))->Init(pos+vec3(0,0,5), kXAxis, kGolden);
            }
        }
    }
    fprintf(my_log, "Init successfully!\n");
}

void Map::Draw(float time){
    if(this->is_loaded == false) return;

    static Ground ground(kZeroVec3, kZAxis, &pebble);
    ground.Draw(height, width);
    for(int x=0; x < height; x++) {
        for (int y=0; y < width; y++) {
            int code = encode(x, y);
            if (state[code] == '#') {
                ((Wall *)models[code])->Draw();
            }
            else if (state[code] == '|' || state[code] == '-') {
                ((Door *)models[code])->Draw(time);
            }
            else if (state[code] == 'k') {
                ((Key *)models[code])->Draw(time*10);
            }
            else if (state[code] == 'e') {
                ((Star *)models[code])->Draw(time*10);
            }
        }
    }
}

bool Map::Check(float x, float y, float time){
    int px = x/10, py = y/10;
    if (px < 0 || py < 0 || px > height || py > width) return false;
    int code = encode(px, py);
    if (state[code] == '#') return false;
    if (state[code] == '-' || state[code] == '|') return ((Door *)models[code])->Check(time);
    return true;
}

inline int Map::encode(vec2 pos){
    return encode(pos.x, pos.y);
}
inline int Map::encode(int x, int y){
    if (x < 0 || y < 0 || x > height || y > width) return 0;
    return x*width + y;
}

char Map::get_state(vec2 pos){
    return get_state(pos.x, pos.y);
}
char Map::get_state(int x, int y){
    int px = x/10, py = y/10;
    return state[encode(px, py)];
}

bool Map::FetchKey(vec2 pos){
    return FetchKey(pos.x, pos.y);
}
bool Map::FetchKey(int x, int y){
    int px = x/10, py = y/10;
    int code = encode(px, py);
    if(state[code] == 'k'){
        state[code] = ' ';
        return 1;
    }
    else {
        return 0;
    }
}

bool Map::OpenDoor(vec2 pos, float time){
    return OpenDoor(pos.x, pos.y, time);
}
bool Map::OpenDoor(int x, int y, float time){
    int px = x/10, py = y/10;
    int code = encode(px, py);
    if(state[code] == '-' || state[code] == '|'){
        ((Door*)models[code])->Open(time, 2);
        return true;
    }
    return false;
}