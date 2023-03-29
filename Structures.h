//
// Created by User on 28/03/2023.
//

#ifndef VOXELENGINE_STRUCTURES_H
#define VOXELENGINE_STRUCTURES_H

#include <glm/glm.hpp>

struct ChunkStruct{
    glm::vec3 pos;
};

struct VoxelStruct{
    int voxType;
    bool isSolid;
};

struct VertexStruct{
    float x;
    float y;
    float z;
};

struct ColourStruct{
    float r;
    float g;
    float b;
    float a;
};


#endif //VOXELENGINE_STRUCTURES_H
