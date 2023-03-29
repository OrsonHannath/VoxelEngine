//
// Created by User on 27/03/2023.
//

#ifndef VOXELENGINE_VOXELWORLD_H
#define VOXELENGINE_VOXELWORLD_H

#include <map>
#include <iostream>
#include "Chunk.h"

class VoxelWorld {
private:
    std::map<std::string, Chunk*> chunksMap;
    GLuint voxelComputeProgramID;
public:
    VoxelWorld();

    void SetComputeProgramID(GLuint voxelComputeProgramID_);
    void AddChunk(Chunk* chunk);
    void LoadChunk(std::string chunkName);
    Chunk GetChunk();
};


#endif //VOXELENGINE_VOXELWORLD_H
