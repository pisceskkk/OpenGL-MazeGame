#pragma once
#include "../utils/model.h"

class Wall:Model{
public:
    using Model::Model;
    using Model::Init;
    void Draw();
};

