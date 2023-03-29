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