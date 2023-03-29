//
// Created by User on 27/03/2023.
//

#include "Chunk.h"

Chunk::Chunk(vec3 position_) {

    position = position_;
}

void Chunk::GenerateChunkVertices(GLuint computeShaderID) {

    // Maximum number of vertices possible per chunk (each voxel will have maximum 3*12 vertices (verticesPerFace * Faces))
    int maxVerticesPossible = size*size*size*3*12;

    // Create an array of Voxel Objects the total size of the chunk
    // Then Create a buffer for the input voxel data
    VoxelStruct voxels[size*size*size];
    GLuint voxelDataBuffer;
    glGenBuffers(1, &voxelDataBuffer);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, voxelDataBuffer);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0 ,voxelDataBuffer);
    glBufferStorage(GL_SHADER_STORAGE_BUFFER, sizeof(voxels), voxels, 0);

    // Create an array of vertex positions (Init at maximum possible vertices for chunk)
    // Then Create a buffer for the output vertices
    std::vector<VertexStruct> vertices(maxVerticesPossible);
    GLuint verticesBuffer;
    glGenBuffers(1, &verticesBuffer);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, verticesBuffer);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1 ,verticesBuffer);
    glBufferStorage(GL_SHADER_STORAGE_BUFFER, vertices.size() * sizeof(VertexStruct), vertices.data(), 0);

    // Create an array of colour positions (Init at maximum possible vertices for chunk)
    // Then Create a buffer for the output vertex colours
    std::vector<ColourStruct> vertex_colours(maxVerticesPossible);
    GLuint vertexColoursBuffer;
    glGenBuffers(1, &vertexColoursBuffer);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, vertexColoursBuffer);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 2 ,vertexColoursBuffer);
    glBufferStorage(GL_SHADER_STORAGE_BUFFER, vertex_colours.size() * sizeof(ColourStruct), vertex_colours.data(), 0);

    // Create a buffer to send in ChunkStruct (Probably shouldn't be doing it like this)
    ChunkStruct chunkStruct = {position};
    ChunkStruct chunkStructArr[] = {chunkStruct};
    GLuint chunkStructBuffer;
    glGenBuffers(1, &chunkStructBuffer);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, chunkStructBuffer);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 3 ,chunkStructBuffer);
    glBufferStorage(GL_SHADER_STORAGE_BUFFER, sizeof(chunkStructArr), chunkStructArr, 0);

    // Compute the shader
    glUseProgram(computeShaderID);
    glDispatchCompute(16, 1, 1);
    glMemoryBarrier(GL_ALL_BARRIER_BITS);

    // Retrieve the output vertices and apply them to local variable
    std::vector<VertexStruct> outVertices;
    outVertices.resize(maxVerticesPossible);
    glGetNamedBufferSubData(verticesBuffer, 0, outVertices.size() * sizeof(VertexStruct), outVertices.data());
    verticesVec.clear();
    for(VertexStruct vs : outVertices){

        //std::cerr << "[" << vs.x << "," << vs.y << "," << vs.z << "], ";

        verticesVec.push_back(vs.x);
        verticesVec.push_back(vs.y);
        verticesVec.push_back(vs.z);
    }

    // Retrieve the output vertex colours and apply them to local variable
    std::vector<ColourStruct> outVertexColours;
    outVertexColours.resize(maxVerticesPossible);
    glGetNamedBufferSubData(vertexColoursBuffer, 0, outVertexColours.size() * sizeof(ColourStruct), outVertexColours.data());
    vertexColoursVec.clear();
    for(ColourStruct cs : outVertexColours){

        vertexColoursVec.push_back(cs.r);
        vertexColoursVec.push_back(cs.g);
        vertexColoursVec.push_back(cs.b);
        vertexColoursVec.push_back(cs.a);
    }

    /*// Check that voxel data is being sent and recieved correctly
    VoxelStruct feedback[size*size*size];
    glGetNamedBufferSubData(voxelDataBuffer, 0, sizeof(feedback), feedback);
    for(int i = 0; i < size*size*size; i++){

        std::cerr << "[" << feedback[i].voxType << "," << feedback[i].isSolid << "], ";
    }*/

    // Create and set the render object of this chunk
    renderObject = new RenderObject(GetChunkName());
    renderObject->SetVertexBufferData(verticesVec);
    renderObject->SetVertexColourData(vertexColoursVec);
}

std::string Chunk::GetChunkName() {

    std::string chunkName = "Chunk: " + std::to_string(position.x) + ", " + std::to_string(position.y) + ", " + std::to_string(position.z);
    return chunkName;
}

RenderObject* Chunk::GetRenderObject() {

    return renderObject;
}