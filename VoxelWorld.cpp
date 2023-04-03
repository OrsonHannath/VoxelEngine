//
// Created by User on 27/03/2023.
//

#include "VoxelWorld.h"

VoxelWorld::VoxelWorld() {

}

void VoxelWorld::LoadChunk(vec3 chunkPos){

    // Find the chunk data
    std::tuple<float, float, float> posTuple(chunkPos.x, chunkPos.y, chunkPos.z);
    Chunk* chunk = chunksMap[posTuple];

    // Update the new chunks neighbouring chunks and the neighbouring chunks' data about this new chunk
    chunk->UpdateChunksNeighbours(CheckNeighbouringChunksLoaded(chunkPos), voxelComputeProgramID); // TODO make a compute shader purely to update the vertices of a face

    // Load the chunks vertices
    chunk->GenerateChunkVertices(voxelComputeProgramID);

    // Set the loadedChunks value to true
    loadedChunks[posTuple] = true;
}

void VoxelWorld::UnloadChunk(vec3 chunkPos){

    // Find the chunk data
    std::tuple<float, float, float> posTuple(chunkPos.x, chunkPos.y, chunkPos.z);
    Chunk* chunk = chunksMap[posTuple];

    // Set the loadedChunks value to false
    loadedChunks[posTuple] = false;
}

void VoxelWorld::AddChunk(Chunk* chunk) {

    vec3 chunkPos = chunk->GetPosition();
    std::tuple<float, float, float> posTuple(chunkPos.x, chunkPos.y, chunkPos.z);

    chunksMap[posTuple] = chunk;
}

void VoxelWorld::SetComputeProgramID(GLuint voxelComputeProgramID_) {

    voxelComputeProgramID = voxelComputeProgramID_;
}

// Returns an array neighbouring chunks load status in order - (front, right, back, left, bottom, top)
std::vector<Chunk*> VoxelWorld::CheckNeighbouringChunksLoaded(vec3 chunkPos) {

    std::vector<Chunk*> tempChunkLoaded;

    // Front
    std::tuple<float, float, float> frontChunkPosTuple(chunkPos.x, chunkPos.y, chunkPos.z + 16); // 16 should be chunk size
    if(loadedChunks.find(frontChunkPosTuple) != loadedChunks.end()){
        loadedChunks[frontChunkPosTuple] ? tempChunkLoaded.push_back(chunksMap[frontChunkPosTuple]) : tempChunkLoaded.push_back(nullptr);
    }else{
        tempChunkLoaded.push_back(nullptr);
    }

    // Right
    std::tuple<float, float, float> rightChunkPosTuple(chunkPos.x + 16, chunkPos.y, chunkPos.z);
    if(loadedChunks.find(rightChunkPosTuple) != loadedChunks.end()){
        loadedChunks[rightChunkPosTuple] ? tempChunkLoaded.push_back(chunksMap[rightChunkPosTuple]) : tempChunkLoaded.push_back(nullptr);
    }else{
        tempChunkLoaded.push_back(nullptr);
    }

    // Back
    std::tuple<float, float, float> backChunkPosTuple(chunkPos.x, chunkPos.y, chunkPos.z - 16);
    if(loadedChunks.find(backChunkPosTuple) != loadedChunks.end()){
        loadedChunks[backChunkPosTuple] ? tempChunkLoaded.push_back(chunksMap[backChunkPosTuple]) : tempChunkLoaded.push_back(nullptr);
    }else{
        tempChunkLoaded.push_back(nullptr);
    }

    // Left
    std::tuple<float, float, float> leftChunkPosTuple(chunkPos.x - 16, chunkPos.y, chunkPos.z);
    if(loadedChunks.find(leftChunkPosTuple) != loadedChunks.end()){
        loadedChunks[leftChunkPosTuple] ? tempChunkLoaded.push_back(chunksMap[leftChunkPosTuple]) : tempChunkLoaded.push_back(nullptr);
    }else{
        tempChunkLoaded.push_back(nullptr);
    }

    // Bottom
    std::tuple<float, float, float> botChunkPosTuple(chunkPos.x, chunkPos.y - 16, chunkPos.z);
    if(loadedChunks.find(botChunkPosTuple) != loadedChunks.end()){
        loadedChunks[botChunkPosTuple] ? tempChunkLoaded.push_back(chunksMap[botChunkPosTuple]) : tempChunkLoaded.push_back(nullptr);
    }else{
        tempChunkLoaded.push_back(nullptr);
    }

    // Top
    std::tuple<float, float, float> topChunkPosTuple(chunkPos.x, chunkPos.y + 16, chunkPos.z);
    if(loadedChunks.find(topChunkPosTuple) != loadedChunks.end()){
        loadedChunks[topChunkPosTuple] ? tempChunkLoaded.push_back(chunksMap[topChunkPosTuple]) : tempChunkLoaded.push_back(nullptr);
    }else{
        tempChunkLoaded.push_back(nullptr);
    }

    return tempChunkLoaded;
}

std::map<std::tuple<float, float, float>, Chunk*> VoxelWorld::GetChunksMap() {

    return chunksMap;
}

Chunk* VoxelWorld::GetChunk(vec3 chunkPos) {

    std::tuple<float, float, float> chunkPosTuple(chunkPos.x, chunkPos.y, chunkPos.z);
    return chunksMap[chunkPosTuple];
}