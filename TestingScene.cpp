//
// Created by User on 26/03/2023.
//

#include "TestingScene.h"

TestingScene::TestingScene(std::string name, GLFWwindow* window_, std::map<std::string, GLuint> GLHandles_) : Scene(name, window_, GLHandles_) {

    // Add a Camera to the Scene
    Camera* camera = new Camera(vec3(0,0,32), window_);
    SetCamera(camera);

    // Add a VoxelWorld to the Scene
    VoxelWorld* voxelWorld_ = new VoxelWorld();
    voxelWorld = voxelWorld_;
    voxelWorld_->SetComputeProgramID(GLHandles["computeProgramID"]);
    voxelWorld_->SetGreedyMeshingComputeProgramID(GLHandles["greedyMeshComputeProgramID"]);

    // Without Greedy Meshing - ~60fps for 12x12x12 chunks rendered (pre scene rendering optimization 6/04/2023)
    // With Chunk Based Greedy Meshing - ~100fps for 12x12x12 chunks rendered (pre scene rendering optimization 6/04/2023)
    // With Chunk Based Greedy Meshing - ~120fps for 12x12x12 chunks rendered (post scene rendering optimization 6/04/2023)
    // With Chunk Based Greedy Meshing and Perlin Noise Generation - ~4fps for 12x12x12 chunks rendered (pre scene rendering optimization 6/04/2023)
    // With Chunk Based Greedy Meshing and Perlin Noise Generation - ~25fps for 12x12x12 chunks rendered (post scene rendering optimization 6/04/2023)
    // With Chunk Based Greedy Meshing and Perlin Noise Generation - ~30fps ~1.5gb for 12x12x12 chunks rendered (post chunk byte size reduction 7/04/2023)

    // Implement LOD
    // Implement chunk loading
    // Make chunks use less data

    int chunkViewDist = 12;
    int chunkSize = 16;
    for(int i = 0; i < chunkViewDist; i++) {
        for (int j = 0; j > -chunkViewDist; j--) {
            for (int k = 0; k < chunkViewDist; k++) {

                // Add a Chunk to the VoxelWorld
                vec3 chunkPosition = vec3((i*chunkSize), (j*chunkSize), (k*chunkSize));
                Chunk *chunk = new Chunk(chunkPosition);
                voxelWorld_->AddChunk(chunk);

                // Generate/Load the chunk
                chunk->GenerateChunkVoxels();
                voxelWorld_->LoadChunk(chunkPosition);

                // Add the chunks render object to the scene
                RenderObject *chunkRenderObject = chunk->GetRenderObject();
                chunkRenderObjectsMapByName[chunkRenderObject->GetName()] = chunkRenderObject;

                // Add a random colour overlay to each chunk
                //Colour randCol = RandomColour();
                //chunkRenderObject->OverlayVertexColours(randCol);
            }
        }
    }
}