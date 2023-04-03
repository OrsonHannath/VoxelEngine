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
    std::map<std::tuple<float, float, float>, Chunk*> chunksMap;
    std::map<std::tuple<float, float, float>, bool> loadedChunks; // Stores whether a chunk is loaded mapped using the key of the chunks name (could optimize key)
    std::map<std::tuple<float, float, float>, std::vector<VertexStruct>> chunksVertexBufferMap;
    std::map<std::tuple<float, float, float>, std::vector<ColourStruct>> chunksColourBufferMap;
    GLuint voxelComputeProgramID;
public:
    VoxelWorld();

    void SetComputeProgramID(GLuint voxelComputeProgramID_);
    void AddChunk(Chunk* chunk);
    void LoadChunk(vec3 chunkPos);
    void UnloadChunk(vec3 chunkPos);

    std::map<std::tuple<float, float, float>, Chunk*> GetChunksMap();
    std::vector<Chunk*> CheckNeighbouringChunksLoaded(vec3 chunkPos);
    Chunk* GetChunk(vec3 chunkPos);
};


#endif //VOXELENGINE_VOXELWORLD_H
