//
// Created by User on 27/03/2023.
//

#ifndef VOXELENGINE_VOXELWORLD_H
#define VOXELENGINE_VOXELWORLD_H

#include <map>
#include <iostream>
#include <vector>
#include "Chunk.h"

class VoxelWorld {
private:
    std::map<std::string, Chunk*> chunksMap;
    std::map<std::string, std::vector<VertexStruct>> chunksVertexBufferMap;
    std::map<std::string, std::vector<ColourStruct>> chunksColourBufferMap;
    GLuint voxelComputeProgramID;
public:
    VoxelWorld();

    void SetComputeProgramID(GLuint voxelComputeProgramID_);
    void AddChunk(Chunk* chunk);
    void LoadChunk(std::string chunkName);

    std::map<std::string, Chunk*> GetChunksMap();
    Chunk* GetChunk(std::string name_);
};


#endif //VOXELENGINE_VOXELWORLD_H
