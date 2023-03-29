//
// Created by User on 27/03/2023.
//

#ifndef VOXELENGINE_CUBE_H
#define VOXELENGINE_CUBE_H

#include <glm/vec3.hpp>
#include "RenderObject.h"

class Cube: public RenderObject{
public:
    Cube(std::string name, vec3 pos, vec3 rot, vec3 scale);
    void SetVertexColours(std::vector<float> vertexColours);
};


#endif //VOXELENGINE_CUBE_H
