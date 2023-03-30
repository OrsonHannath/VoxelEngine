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

class Chunk {
private:
    vec3 position;
    static const int size = 16;
    std::map<std::string, Voxel> voxelMap;
    std::vector<VertexStruct> verticesVec; // Probably don't need to store here
    std::vector<ColourStruct> vertexColoursVec; // Probably don't need to store here
    RenderObject* renderObject;
public:
    Chunk(vec3 position_);

    void GenerateChunkVertices(GLuint computeShaderID); // Should expand this to be based on noise
    std::string GetChunkName();
    RenderObject* GetRenderObject();
};


#endif //VOXELENGINE_CHUNK_H
