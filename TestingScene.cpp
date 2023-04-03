//
// Created by User on 26/03/2023.
//

#include "TestingScene.h"

TestingScene::TestingScene(std::string name, GLFWwindow* window_, std::map<std::string, GLuint> GLHandles_) : Scene(name, window_, GLHandles_) {

    // Stuff will not render if its colours are not specified so should work out a way to have a default color if it isnt set

    // Add a Camera to the Scene
    Camera* camera = new Camera(vec3(0,0,32), window_);
    SetCamera(camera);

    // Add a VoxelWorld to the Scene
    VoxelWorld* voxelWorld_ = new VoxelWorld();
    voxelWorld = voxelWorld_;
    voxelWorld_->SetComputeProgramID(GLHandles["computeProgramID"]);

    /*// Add a Chunk to the VoxelWorld
    Chunk *chunk = new Chunk(vec3((-8), (-8), (-16)));
    voxelWorld_->AddChunk(chunk);
    // Generate/Load the chunk
    chunk->GenerateChunkVoxels();
    voxelWorld_->LoadChunk(chunk->GetChunkName());
    // Add the chunks render object to the scene
    RenderObject *chunkRenderObject = chunk->GetRenderObject();
    chunkRenderObjectsMapByName[chunkRenderObject->GetName()] = chunkRenderObject;


    // Add a Chunk to the VoxelWorld
    Chunk *chunk2 = new Chunk(vec3((8), (-8), (-16)));
    voxelWorld_->AddChunk(chunk2);
    // Generate/Load the chunk
    chunk2->GenerateChunkVoxels();
    voxelWorld_->LoadChunk(chunk2->GetChunkName());
    // Add the chunks render object to the scene
    RenderObject *chunkRenderObject2 = chunk2->GetRenderObject();
    chunkRenderObjectsMapByName[chunkRenderObject2->GetName()] = chunkRenderObject2;

    // Add a Chunk to the VoxelWorld
    Chunk *chunk3 = new Chunk(vec3((8), (8), (-16)));
    voxelWorld_->AddChunk(chunk3);
    // Generate/Load the chunk
    chunk3->GenerateChunkVoxels();
    voxelWorld_->LoadChunk(chunk3->GetChunkName());
    // Add the chunks render object to the scene
    RenderObject *chunkRenderObject3 = chunk3->GetRenderObject();
    chunkRenderObjectsMapByName[chunkRenderObject3->GetName()] = chunkRenderObject3;

    // Add a Chunk to the VoxelWorld
    Chunk *chunk4 = new Chunk(vec3((8), (-8), (-32)));
    voxelWorld_->AddChunk(chunk4);
    // Generate/Load the chunk
    chunk4->GenerateChunkVoxels();
    voxelWorld_->LoadChunk(chunk4->GetChunkName());
    // Add the chunks render object to the scene
    RenderObject *chunkRenderObject4 = chunk4->GetRenderObject();
    chunkRenderObjectsMapByName[chunkRenderObject4->GetName()] = chunkRenderObject4;

    // Add a Chunk to the VoxelWorld
    Chunk *chunk5 = new Chunk(vec3((8), (-8), (-48)));
    voxelWorld_->AddChunk(chunk5);
    // Generate/Load the chunk
    chunk5->GenerateChunkVoxels();
    voxelWorld_->LoadChunk(chunk5->GetChunkName());
    // Add the chunks render object to the scene
    RenderObject *chunkRenderObject5 = chunk5->GetRenderObject();
    chunkRenderObjectsMapByName[chunkRenderObject5->GetName()] = chunkRenderObject5;

    // Add a Chunk to the VoxelWorld
    Chunk *chunk6 = new Chunk(vec3((8), (8), (-32)));
    voxelWorld_->AddChunk(chunk6);
    // Generate/Load the chunk
    chunk6->GenerateChunkVoxels();
    voxelWorld_->LoadChunk(chunk6->GetChunkName());
    // Add the chunks render object to the scene
    RenderObject *chunkRenderObject6 = chunk6->GetRenderObject();
    chunkRenderObjectsMapByName[chunkRenderObject6->GetName()] = chunkRenderObject6;

    // Add a Chunk to the VoxelWorld
    Chunk *chunk7 = new Chunk(vec3((24), (-8), (-16)));
    voxelWorld_->AddChunk(chunk7);
    // Generate/Load the chunk
    chunk7->GenerateChunkVoxels();
    voxelWorld_->LoadChunk(chunk7->GetChunkName());
    // Add the chunks render object to the scene
    RenderObject *chunkRenderObject7 = chunk7->GetRenderObject();
    chunkRenderObjectsMapByName[chunkRenderObject7->GetName()] = chunkRenderObject7;

    // Add a Chunk to the VoxelWorld
    Chunk *chunk8 = new Chunk(vec3((40), (-8), (-16)));
    voxelWorld_->AddChunk(chunk8);
    // Generate/Load the chunk
    chunk8->GenerateChunkVoxels();
    voxelWorld_->LoadChunk(chunk8->GetChunkName());
    // Add the chunks render object to the scene
    RenderObject *chunkRenderObject8 = chunk8->GetRenderObject();
    chunkRenderObjectsMapByName[chunkRenderObject8->GetName()] = chunkRenderObject8;*/

    // Without Greedy Meshing - ~60fps for 12x12x12 chunks rendered

    int chunkViewDist = 12;
    int chunkSize = 16;
    for(int i = ceil(-(chunkViewDist/2.0f)); i < ceil(chunkViewDist/2.0f); i++) {
        for (int j = ceil(-(chunkViewDist/2.0f)); j < ceil(chunkViewDist/2.0f); j++) {
            for (int k = ceil(-(chunkViewDist/2.0f)); k < ceil(chunkViewDist/2.0f); k++) {

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