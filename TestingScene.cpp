//
// Created by User on 26/03/2023.
//

#include "TestingScene.h"

TestingScene::TestingScene(std::string name, GLFWwindow* window_, std::map<std::string, GLuint> GLHandles_) : Scene(name, window_, GLHandles_) {

    // Stuff will not render if its colours are not specified so should work out a way to have a default color if it isnt set

    // Add a Camera to the Scene
    Camera* camera = new Camera(vec3(0,0,5), window_);
    SetCamera(camera);

    // Add a VoxelWorld to the Scene
    VoxelWorld* voxelWorld_ = new VoxelWorld();
    voxelWorld = voxelWorld_;
    voxelWorld_->SetComputeProgramID(GLHandles["computeProgramID"]);

    int chunkViewDist = 2;
    int chunkSize = 16;
    for(int i = ceil(-(chunkViewDist/2.0f)); i < ceil(chunkViewDist/2.0f); i++) {
        for (int j = ceil(-(chunkViewDist/2.0f)); j < ceil(chunkViewDist/2.0f); j++) {
            for (int k = ceil(-(chunkViewDist/2.0f)); k < ceil(chunkViewDist/2.0f); k++) {

                // Add a Chunk to the VoxelWorld
                Chunk *chunk = new Chunk(vec3((i*chunkSize), (j*chunkSize), (k*chunkSize)));
                voxelWorld_->AddChunk(chunk);

                // Generate/Load the chunk
                voxelWorld_->LoadChunk(chunk->GetChunkName());

                // Add the chunks render object to the scene
                RenderObject *chunkRenderObject = chunk->GetRenderObject();
                chunkRenderObjectsMapByName[chunkRenderObject->GetName()] = chunkRenderObject;

                // Add a random colour overlay to each chunk
                Colour randCol = RandomColour();
                chunkRenderObject->OverlayVertexColours(randCol);
            }
        }
    }
}