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
    std::vector<VoxelStruct> voxels(size*size*size);
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            for(int k = 0; k < size; k++){

                int randX = rand() % 2;
                voxels.at(i + size * (j + size * k)).isSolid = 1;

                int randC = rand() % 255;
                voxels.at(i + size * (j + size * k)).voxType = randC;
            }
        }
    }

    GLuint voxelDataBuffer;
    glGenBuffers(1, &voxelDataBuffer);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, voxelDataBuffer);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0 ,voxelDataBuffer);
    glBufferStorage(GL_SHADER_STORAGE_BUFFER, voxels.size() * sizeof(VoxelStruct), voxels.data(), 0);

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
    verticesVec = outVertices;
    /*for(VertexStruct vs : outVertices){

        //std::cerr << "[" << vs.x << "," << vs.y << "," << vs.z << "], ";
    }*/

    // Retrieve the output vertex colours and apply them to local variable
    std::vector<ColourStruct> outVertexColours;
    outVertexColours.resize(maxVerticesPossible);
    glGetNamedBufferSubData(vertexColoursBuffer, 0, outVertexColours.size() * sizeof(ColourStruct), outVertexColours.data());
    vertexColoursVec.clear();
    vertexColoursVec = outVertexColours;
    /*for(ColourStruct cs : outVertexColours){

        std::cerr << "[" << cs.r << "," << cs.g << "," << cs.b << "," << cs.a << "], ";
    }*/

    // Remove all vertices/faces that cannot possibly render from ourVectors (Vertices and Vertex Colours Vectors should be same size)
    verticesVec.clear();
    vertexColoursVec.clear();
    for(int i = 0; i < outVertices.size()/3; i++){

        int iAdjPos = i*3;
        if(!(outVertices.at(iAdjPos) == outVertices.at(iAdjPos+1) && outVertices.at(iAdjPos) == outVertices.at(iAdjPos+2))){

            // Push the vertices to the chunks vertices since they are not all the same value (i.e. not null)
            verticesVec.push_back(outVertices.at(iAdjPos));
            verticesVec.push_back(outVertices.at(iAdjPos+1));
            verticesVec.push_back(outVertices.at(iAdjPos+2));

            // Push the vertex colours to the chunks vertex colours since they are not all the same value (i.e. not null)
            vertexColoursVec.push_back(outVertexColours.at(iAdjPos));
            vertexColoursVec.push_back(outVertexColours.at(iAdjPos+1));
            vertexColoursVec.push_back(outVertexColours.at(iAdjPos+2));
        }
    }

    /*// Check that voxel data is being sent and recieved correctly
    std::vector<VoxelStruct> voxelFeedback(size*size*size);
    glGetNamedBufferSubData(voxelDataBuffer, 0, voxelFeedback.size() * sizeof(VoxelStruct), voxelFeedback.data());
    for(VoxelStruct voxelStruct : voxelFeedback){

        std::cerr << "[" << voxelStruct.voxType << "," << voxelStruct.isSolid << "], ";
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