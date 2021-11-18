#pragma once
#include "../utils/model.h"

class Ground: Model{
public:
    using Model::Model;
    void Draw(GLint x_slices, GLint y_slices);
};