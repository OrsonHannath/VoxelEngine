//
// Created by User on 27/03/2023.
//

#ifndef VOXELENGINE_VOXELWORLD_H
#define VOXELENGINE_VOXELWORLD_H

#include <map>
#include <iostream>
#include <vector>
#include <future>
#include "Chunk.h"

class VoxelWorld {
private:
    std::map<std::tuple<int, int, int>, Chunk*> chunksMap;
    std::map<std::tuple<int, int, int>, bool> loadedChunks; // Stores whether a chunk is loaded mapped using the key of the chunks name (could optimize key)
    GLuint voxelComputeProgramID;
    GLuint greedyMeshComputeProgramID;
    int chunkSize = 16;

    std::vector<std::future<void>> m_Futures;
    std::mutex s_Mutex;
public:
    VoxelWorld();

    void UpdateChunks(int viewDist, vec3 viewerPos);

    void SetComputeProgramID(GLuint voxelComputeProgramID_);
    void SetGreedyMeshingComputeProgramID(GLuint greedyMeshComputeProgramID_);
    void LoadChunk(ivec3 chunkPos);
    void UnloadChunk(ivec3 chunkPos);

    std::map<std::tuple<int, int, int>, Chunk*> GetChunksMap();
    std::vector<Chunk*> CheckNeighbouringChunksLoaded(ivec3 chunkPos);
    Chunk* GetChunk(ivec3 chunkPos);
};


#endif //VOXELENGINE_VOXELWORLD_H
