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
    VoxelWorld* voxelWorld = new VoxelWorld();
    voxelWorld->SetComputeProgramID(GLHandles["computeProgramID"]);

    std::cout << GLHandles["computeProgramID"] << std::endl;

    // Add a Chunk to the VoxelWorld
    Chunk* chunk = new Chunk(vec3(0, 0, 0));
    voxelWorld->AddChunk(chunk);

    // Generate/Load the chunk
    voxelWorld->LoadChunk(chunk->GetChunkName());

    // Add the chunks render object to the scene
    RenderObject* chunkRenderObject = chunk->GetRenderObject();
    objectsMapByName[chunkRenderObject->GetName()] = chunkRenderObject;
}