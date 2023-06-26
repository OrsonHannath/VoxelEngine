//
// Created by User on 27/03/2023.
//

#include "VoxelWorld.h"

VoxelWorld::VoxelWorld() {

}

// Single-thread chunk loading and unloading
void VoxelWorld::UpdateChunks(int viewDist, vec3 viewerPos) {

    // Check if chunks surrounding viewerPos exist and if so update them
    for(int i = 0; i < viewDist; i++){
        for(int j = 0; j < viewDist; j++){
            for(int k = 0; k < viewDist; k++){

                // Get chunk position
                int x = i - (int)floor(viewDist/2); // These are floored to prevent rounding issues where 0.5 = 1, and -0.5 = -1
                int y = j - (int)floor(viewDist/2);
                int z = k - (int)floor(viewDist/2);
                ivec3 chunkPos = {floor(((viewerPos.x - (chunkSize/2)) + (x * chunkSize)) / (float)chunkSize) * chunkSize,
                                  floor(((viewerPos.y - (chunkSize/2)) + (y * chunkSize)) / (float)chunkSize) * chunkSize,
                                  floor(((viewerPos.z - (chunkSize/2)) + (z * chunkSize)) / (float)chunkSize) * chunkSize};

                // Make sure the chunk is within the viewDistance
                if(sqrt(x*x + y*y + z*z) <= viewDist * chunkSize){

                    // Make an int tuple for the position
                    std::tuple<int, int, int> posTuple(chunkPos.x, chunkPos.y, chunkPos.z);

                    // Check if a chunk exists at this position already
                    if(chunksMap.find(posTuple) == chunksMap.end()){

                        // Make the chunk
                        std::tuple<int, int, int> posTuple(chunkPos.x, chunkPos.y, chunkPos.z);
                        Chunk* chunk = new Chunk(chunkPos);
                        chunksMap[posTuple] = chunk;

                        //m_Futures.push_back(std::async(std::launch::async, &VoxelWorld::LoadChunk, this, chunkPos)); // This doesn't
                        LoadChunk(chunkPos); // This works
                    }
                }
            }
        }
    }
}

void VoxelWorld::LoadChunk(ivec3 chunkPos){

    // Get the chunk
    std::tuple<int, int, int> posTuple(chunkPos.x, chunkPos.y, chunkPos.z);
    Chunk* chunk = chunksMap[posTuple];

    // Generate the chunks voxels
    chunk->GenerateChunkVoxels();

    // Update the new chunks neighbouring chunks and the neighbouring chunks' data about this new chunk
    chunk->UpdateChunksNeighbours(CheckNeighbouringChunksLoaded(chunkPos), voxelComputeProgramID, greedyMeshComputeProgramID); // TODO make a compute shader purely to update the vertices of a face

    // Load the chunks vertices
    chunk->GenerateChunkVertices(voxelComputeProgramID, greedyMeshComputeProgramID);

    // Set the loadedChunks value to true
    loadedChunks[posTuple] = true;

    // Set the chunks loaded value to true
    chunk->SetLoaded(true);
}

void VoxelWorld::UnloadChunk(ivec3 chunkPos){

    // Find the chunk data
    std::tuple<int, int, int> posTuple(chunkPos.x, chunkPos.y, chunkPos.z);

    // Check if the chunk is loaded
    if(chunksMap.find(posTuple) != chunksMap.end()){

        // Set the loadedChunks value to false
        loadedChunks[posTuple] = false;

        // Delete the object from memory
        delete chunksMap[posTuple];

        // Remove the pointer to the chunk from chunks map
        chunksMap.erase(posTuple);
    }
}

void VoxelWorld::SetComputeProgramID(GLuint voxelComputeProgramID_) {

    voxelComputeProgramID = voxelComputeProgramID_;
}

void VoxelWorld::SetGreedyMeshingComputeProgramID(GLuint greedyMeshComputeProgramID_) {

    greedyMeshComputeProgramID = greedyMeshComputeProgramID_;
}

// Returns an array neighbouring chunks load status in order - (front, right, back, left, bottom, top)
std::vector<Chunk*> VoxelWorld::CheckNeighbouringChunksLoaded(ivec3 chunkPos) {

    std::vector<Chunk*> tempChunkLoaded;

    // Front
    std::tuple<int, int, int> frontChunkPosTuple(chunkPos.x, chunkPos.y, chunkPos.z + 16); // 16 should be chunk size
    if(loadedChunks.find(frontChunkPosTuple) != loadedChunks.end()){
        loadedChunks[frontChunkPosTuple] ? tempChunkLoaded.push_back(chunksMap[frontChunkPosTuple]) : tempChunkLoaded.push_back(nullptr);
    }else{
        tempChunkLoaded.push_back(nullptr);
    }

    // Right
    std::tuple<int, int, int> rightChunkPosTuple(chunkPos.x + 16, chunkPos.y, chunkPos.z);
    if(loadedChunks.find(rightChunkPosTuple) != loadedChunks.end()){
        loadedChunks[rightChunkPosTuple] ? tempChunkLoaded.push_back(chunksMap[rightChunkPosTuple]) : tempChunkLoaded.push_back(nullptr);
    }else{
        tempChunkLoaded.push_back(nullptr);
    }

    // Back
    std::tuple<int, int, int> backChunkPosTuple(chunkPos.x, chunkPos.y, chunkPos.z - 16);
    if(loadedChunks.find(backChunkPosTuple) != loadedChunks.end()){
        loadedChunks[backChunkPosTuple] ? tempChunkLoaded.push_back(chunksMap[backChunkPosTuple]) : tempChunkLoaded.push_back(nullptr);
    }else{
        tempChunkLoaded.push_back(nullptr);
    }

    // Left
    std::tuple<int, int, int> leftChunkPosTuple(chunkPos.x - 16, chunkPos.y, chunkPos.z);
    if(loadedChunks.find(leftChunkPosTuple) != loadedChunks.end()){
        loadedChunks[leftChunkPosTuple] ? tempChunkLoaded.push_back(chunksMap[leftChunkPosTuple]) : tempChunkLoaded.push_back(nullptr);
    }else{
        tempChunkLoaded.push_back(nullptr);
    }

    // Bottom
    std::tuple<int, int, int> botChunkPosTuple(chunkPos.x, chunkPos.y - 16, chunkPos.z);
    if(loadedChunks.find(botChunkPosTuple) != loadedChunks.end()){
        loadedChunks[botChunkPosTuple] ? tempChunkLoaded.push_back(chunksMap[botChunkPosTuple]) : tempChunkLoaded.push_back(nullptr);
    }else{
        tempChunkLoaded.push_back(nullptr);
    }

    // Top
    std::tuple<int, int, int> topChunkPosTuple(chunkPos.x, chunkPos.y + 16, chunkPos.z);
    if(loadedChunks.find(topChunkPosTuple) != loadedChunks.end()){
        loadedChunks[topChunkPosTuple] ? tempChunkLoaded.push_back(chunksMap[topChunkPosTuple]) : tempChunkLoaded.push_back(nullptr);
    }else{
        tempChunkLoaded.push_back(nullptr);
    }

    return tempChunkLoaded;
}

std::map<std::tuple<int, int, int>, Chunk*> VoxelWorld::GetChunksMap() {

    return chunksMap;
}

Chunk* VoxelWorld::GetChunk(ivec3 chunkPos) {

    std::tuple<int, int, int> chunkPosTuple(chunkPos.x, chunkPos.y, chunkPos.z);
    return chunksMap[chunkPosTuple];
}