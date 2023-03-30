//
// Created by User on 27/03/2023.
//

#include "VoxelWorld.h"

VoxelWorld::VoxelWorld() {

}

void VoxelWorld::LoadChunk(std::string chunkName){

    Chunk* chunk = chunksMap[chunkName];
    chunk->GenerateChunkVertices(voxelComputeProgramID);
}

void VoxelWorld::AddChunk(Chunk* chunk) {

    std::string chunkName = chunk->GetChunkName();
    chunksMap[chunkName] = chunk;
}

void VoxelWorld::SetComputeProgramID(GLuint voxelComputeProgramID_) {

    voxelComputeProgramID = voxelComputeProgramID_;
}

std::map<std::string, Chunk*> VoxelWorld::GetChunksMap() {

    return chunksMap;
}

Chunk* VoxelWorld::GetChunk(std::string name_) {

    return chunksMap[name_];
}