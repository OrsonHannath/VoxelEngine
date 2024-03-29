//
// Created by User on 27/03/2023.
//

#ifndef VOXELENGINE_CHUNK_H
#define VOXELENGINE_CHUNK_H

#include <iostream>
#include <map>
#include <glew.h>
#include <vector>
#include <cmath>
#include <memory>
#include "Camera.h"
#include "Object.h"
#include "RenderObject.h"
#include "Voxel.h"
#include "Structures.h"
#include "PerlinNoise.h"

class Chunk {
private:
    ivec3 position;
    int LOD;
    static const int size = 16;
    VoxelStruct chunkVoxels[size][size][size];
    RenderObject* renderObject;
    bool loaded = false;

    // Neighbours Voxels Information
    int chunkNeighbouringFaceVoxels[6][size][size] = {0}; // Voxel solidity information for each neighbouring face (front, right, back, left, bottom, top)
public:
    Chunk(ivec3 position_);

    void GenerateChunkVertices(GLuint computeShaderID, GLuint greedyMeshComputeShaderID);
    void GenerateChunkVoxels();
    void UpdateChunkNeighbour(Chunk* chunkN, int faceIndex);
    void UpdateChunksNeighbours(std::vector<Chunk*> chunkNeighbours, GLuint computeShaderID, GLuint greedyMeshComputeShaderID);

    void SetLOD(int lod);
    void SetLoaded(bool loaded_);

    ivec3 GetPosition();
    int GetLOD();
    bool GetLoaded();
    std::string GetChunkName();
    RenderObject* GetRenderObject();
    std::vector<std::vector<int>> GetChunkFaceSolidity(int faceIndex); // Index Order: front, right, back, left, bottom, top
};


#endif //VOXELENGINE_CHUNK_H
