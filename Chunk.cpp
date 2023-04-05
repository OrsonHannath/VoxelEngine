//
// Created by User on 27/03/2023.
//

#include "Chunk.h"

Chunk::Chunk(vec3 position_) {

    position = position_;
}

void Chunk::GenerateChunkVoxels() {

    // Find where the random artefacts are coming from
    // Pass in surrounding chunks border voxels so that we know 100% what needs to be rendered

    PerlinNoise perlinNoise = PerlinNoise();

    std::cout << GetChunkName() << std::endl;

    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            for(int k = 0; k < size; k++){

                chunkVoxels[i][j][k].voxType = 0;

                int voxelWSX = floor(position.x) + i;
                int voxelWSY = floor(position.y) + j;
                int voxelWSZ = floor(position.z) + k;

                float freq = 0.2;
                float amp = 5;
                float surfaceY = 8 + sin(voxelWSZ * freq)*amp;

                // Set the voxel isSolid
                if(voxelWSY < surfaceY){

                    chunkVoxels[i][j][k].isSolid = 1;
                    chunkVoxels[i][j][k].voxType = 5;//(rand() % 10); // Only give it a type if it is a solid
                }else{
                    chunkVoxels[i][j][k].isSolid = 0;
                }
            }
        }
    }
}

void Chunk::GenerateChunkVertices(GLuint computeShaderID, GLuint greedyMeshComputeShaderID) {

    // Maximum number of vertices possible per chunk (each voxel will have maximum 3*12 vertices (verticesPerFace * Faces))
    int maxVerticesPossible = size*size*size*3*12;

    // Create an array of Voxel Objects the total size of the chunk
    // Then Create a buffer for the input voxel data
    std::vector<VoxelStruct> voxels;
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            for(int k = 0; k < size; k++){

                voxels.push_back(chunkVoxels[i][j][k]);
            }
        }
    }

    // Create an array of Neighbouring Face Voxel Objects
    // Then Create a buffer for the input voxel data
    std::vector<int> neighbouringFaceVoxels;
    for(int i = 0; i < 6; i++){
        for(int j = 0; j < size; j++){
            for(int k = 0; k < size; k++){

                neighbouringFaceVoxels.push_back(chunkNeighbouringFaceVoxels[i][j][k]);
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

    // Create a buffer to send in neighbouring chunk faces
    GLuint neighbouringFacesBuffer;
    glGenBuffers(1, &neighbouringFacesBuffer);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, neighbouringFacesBuffer);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 4 ,neighbouringFacesBuffer);
    glBufferStorage(GL_SHADER_STORAGE_BUFFER, neighbouringFaceVoxels.size() * sizeof(int), neighbouringFaceVoxels.data(), 0);

    // Compute the shader
    glUseProgram(computeShaderID);
    glDispatchCompute(16, 1, 1);
    glMemoryBarrier(GL_ALL_BARRIER_BITS);

    // Setup and Run the Greedy Meshing Compute Shader
    glUseProgram(greedyMeshComputeShaderID);
    glDispatchCompute(6, 1, 1);
    glMemoryBarrier(GL_ALL_BARRIER_BITS);

    // Retrieve the output vertices and apply them to local variable
    std::vector<VertexStruct> outVertices;
    outVertices.resize(maxVerticesPossible);
    glGetNamedBufferSubData(verticesBuffer, 0, outVertices.size() * sizeof(VertexStruct), outVertices.data());
    verticesVec.clear();
    /*for(VertexStruct vs : outVertices){

        //std::cerr << "[" << vs.x << "," << vs.y << "," << vs.z << "], ";
    }*/

    // Retrieve the output vertex colours and apply them to local variable
    std::vector<ColourStruct> outVertexColours;
    outVertexColours.resize(maxVerticesPossible);
    glGetNamedBufferSubData(vertexColoursBuffer, 0, outVertexColours.size() * sizeof(ColourStruct), outVertexColours.data());
    vertexColoursVec.clear();
    /*for(ColourStruct cs : outVertexColours){

        std::cerr << "[" << cs.r << "," << cs.g << "," << cs.b << "," << cs.a << "], ";
    }*/

    // Remove all vertices/faces that cannot possibly render from outVectors (Vertices and Vertex Colours Vectors should be same size)
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
    for(VertexStruct vs : verticesVec){
        if(vs.x == 0 || vs.y == 0 || vs.z == 0) {
            std::cout << "[" << vs.x << "," << vs.y << "," << vs.z << "], ";
        }
    }

    // Check that voxel data is being sent and received correctly
    /*std::vector<VoxelStruct> voxelFeedback(size*size*size);
    glGetNamedBufferSubData(voxelDataBuffer, 0, voxelFeedback.size() * sizeof(VoxelStruct), voxelFeedback.data());
    for(VoxelStruct voxelStruct : voxelFeedback){

        std::cerr << "[" << voxelStruct.voxType << "," << voxelStruct.isSolid << "], ";
    }*/

    // Create and set the render object of this chunk
    renderObject = new RenderObject(GetChunkName());
    renderObject->SetVertexBufferData(verticesVec);
    renderObject->SetVertexColourData(vertexColoursVec);
}

// chunkNeighboursLoaded has pointers to neighbouring chunks in order - (front, right, back, left, bottom, top)
// Function updates the chunkNeighbouringFaceVoxels var for this chunk, this is based on the chunkNeighboursLoaded input
// which specifies if there are neighbouring chunks that are already loaded
void Chunk::UpdateChunksNeighbours(std::vector<Chunk*> chunkNeighboursLoaded, GLuint computeShaderID, GLuint greedyMeshComputeShaderID) {

    // Array that remaps the faceIndex i.e. front face maps to back face. (normal order - front, right, back, left, bottom, top)
    int remapFaceIndex[] = {2, 3, 0, 1, 5, 4};

    // Update front neighbour
    if(chunkNeighboursLoaded.at(0) != nullptr){

        // Update this chunks information about the neighbouring chunk
        UpdateChunkNeighbour(chunkNeighboursLoaded.at(0), 0);

        // Update the neighbouring chunks' information about this chunk and regenerate its vertices
        chunkNeighboursLoaded.at(0)->UpdateChunkNeighbour(this, remapFaceIndex[0]);
        chunkNeighboursLoaded.at(0)->GenerateChunkVertices(computeShaderID, greedyMeshComputeShaderID);
    }

    // Update right neighbour
    if(chunkNeighboursLoaded.at(1) != nullptr){

        // Update this chunks information about the neighbouring chunk
        UpdateChunkNeighbour(chunkNeighboursLoaded.at(1), 1);

        // Update the neighbouring chunks' information about this chunk
        chunkNeighboursLoaded.at(1)->UpdateChunkNeighbour(this, remapFaceIndex[1]);
        chunkNeighboursLoaded.at(1)->GenerateChunkVertices(computeShaderID, greedyMeshComputeShaderID);
    }

    // Update back neighbour
    if(chunkNeighboursLoaded.at(2) != nullptr){

        // Update this chunks information about the neighbouring chunk
        UpdateChunkNeighbour(chunkNeighboursLoaded.at(2), 2);

        // Update the neighbouring chunks' information about this chunk
        chunkNeighboursLoaded.at(2)->UpdateChunkNeighbour(this, remapFaceIndex[2]);
        chunkNeighboursLoaded.at(2)->GenerateChunkVertices(computeShaderID, greedyMeshComputeShaderID);
    }

    // Update left neighbour
    if(chunkNeighboursLoaded.at(3) != nullptr){

        // Update this chunks information about the neighbouring chunk
        UpdateChunkNeighbour(chunkNeighboursLoaded.at(3), 3);

        // Update the neighbouring chunks' information about this chunk
        chunkNeighboursLoaded.at(3)->UpdateChunkNeighbour(this, remapFaceIndex[3]);
        chunkNeighboursLoaded.at(3)->GenerateChunkVertices(computeShaderID, greedyMeshComputeShaderID);
    }

    // Update bottom neighbour
    if(chunkNeighboursLoaded.at(4) != nullptr){

        // Update this chunks information about the neighbouring chunk
        UpdateChunkNeighbour(chunkNeighboursLoaded.at(4), 4);

        // Update the neighbouring chunks' information about this chunk
        chunkNeighboursLoaded.at(4)->UpdateChunkNeighbour(this, remapFaceIndex[4]);
        chunkNeighboursLoaded.at(4)->GenerateChunkVertices(computeShaderID, greedyMeshComputeShaderID);
    }

    // Update top neighbour
    if(chunkNeighboursLoaded.at(5) != nullptr){

        // Update this chunks information about the neighbouring chunk
        UpdateChunkNeighbour(chunkNeighboursLoaded.at(5), 5);

        // Update the neighbouring chunks' information about this chunk
        chunkNeighboursLoaded.at(5)->UpdateChunkNeighbour(this, remapFaceIndex[5]);
        chunkNeighboursLoaded.at(5)->GenerateChunkVertices(computeShaderID, greedyMeshComputeShaderID);
    }
}

// Function sets values of chunkNeighbouringFaceVoxels, which stores information on this chunk about the solidity of neighbouring chunks faces.
void Chunk::UpdateChunkNeighbour(Chunk *chunkN, int faceIndex) {

    // Array that remaps the faceIndex i.e. front face maps to back face. (normal order - front, right, back, left, bottom, top)
    int remapFaceIndex[] = {2, 3, 0, 1, 5, 4};

    std::vector<std::vector<int>> faceVec = chunkN->GetChunkFaceSolidity(remapFaceIndex[faceIndex]);
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){

            chunkNeighbouringFaceVoxels[faceIndex][i][j] = faceVec.at(i).at(j);
        }
    }
}

// Face Index Order: front, right, back, left, bottom, top
// Returns the voxel solidity data for the specified face of this chunk
std::vector<std::vector<int>> Chunk::GetChunkFaceSolidity(int faceIndex) {

    std::vector<std::vector<int>> faceSolidityVec;
    faceSolidityVec.reserve(size);

    // Return front face voxel information
    if(faceIndex == 0){
        for(int i = 0; i < size; i++){

            std::vector<int> faceSoliditySubVec;
            faceSoliditySubVec.reserve(size);

            for(int j = 0; j < size; j++){

                faceSoliditySubVec.push_back((int)chunkVoxels[i][j][size-1].isSolid);
            }

            faceSolidityVec.push_back(faceSoliditySubVec);
        }

        return faceSolidityVec;
    }

    // Return right face voxel information
    if(faceIndex == 1){
        for(int i = 0; i < size; i++){

            std::vector<int> faceSoliditySubVec;
            faceSoliditySubVec.reserve(size);

            for(int j = 0; j < size; j++){

                faceSoliditySubVec.push_back((int)chunkVoxels[size-1][i][j].isSolid);
            }

            faceSolidityVec.push_back(faceSoliditySubVec);
        }

        return faceSolidityVec;
    }

    // Return back face voxel information
    if(faceIndex == 2){
        for(int i = 0; i < size; i++){

            std::vector<int> faceSoliditySubVec;
            faceSoliditySubVec.reserve(size);

            for(int j = 0; j < size; j++){

                faceSoliditySubVec.push_back((int)chunkVoxels[i][j][0].isSolid);
            }

            faceSolidityVec.push_back(faceSoliditySubVec);
        }

        return faceSolidityVec;
    }

    // Return left face voxel information
    if(faceIndex == 3){
        for(int i = 0; i < size; i++){

            std::vector<int> faceSoliditySubVec;
            faceSoliditySubVec.reserve(size);

            for(int j = 0; j < size; j++){

                faceSoliditySubVec.push_back((int)chunkVoxels[0][i][j].isSolid);
            }

            faceSolidityVec.push_back(faceSoliditySubVec);
        }

        return faceSolidityVec;
    }

    // Return bottom face voxel information
    if(faceIndex == 4){
        for(int i = 0; i < size; i++){

            std::vector<int> faceSoliditySubVec;
            faceSoliditySubVec.reserve(size);

            for(int j = 0; j < size; j++){

                faceSoliditySubVec.push_back((int)chunkVoxels[i][0][j].isSolid);
            }

            faceSolidityVec.push_back(faceSoliditySubVec);
        }

        return faceSolidityVec;
    }

    // Return top face voxel information
    if(faceIndex == 5){
        for(int i = 0; i < size; i++){

            std::vector<int> faceSoliditySubVec;
            faceSoliditySubVec.reserve(size);

            for(int j = 0; j < size; j++){

                faceSoliditySubVec.push_back((int)chunkVoxels[i][size-1][j].isSolid);
            }

            faceSolidityVec.push_back(faceSoliditySubVec);
        }

        return faceSolidityVec;
    }

    return faceSolidityVec;
}

vec3 Chunk::GetPosition() {

    return position;
}

std::string Chunk::GetChunkName() {

    std::string chunkName = "Chunk: " + std::to_string(position.x) + ", " + std::to_string(position.y) + ", " + std::to_string(position.z);
    return chunkName;
}

RenderObject* Chunk::GetRenderObject() {

    return renderObject;
}