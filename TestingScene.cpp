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

    int initChunksDistance = 3;
    voxelWorld->UpdateChunks(initChunksDistance,Scene::GetCamera()->GetPosition());

    // Without Greedy Meshing - ~60fps for 12x12x12 chunks rendered (pre scene rendering optimization 6/04/2023)
    // With Chunk Based Greedy Meshing - ~100fps for 12x12x12 chunks rendered (pre scene rendering optimization 6/04/2023)
    // With Chunk Based Greedy Meshing - ~120fps for 12x12x12 chunks rendered (post scene rendering optimization 6/04/2023)
    // With Chunk Based Greedy Meshing and Perlin Noise Generation - ~4fps for 12x12x12 chunks rendered (pre scene rendering optimization 6/04/2023)
    // With Chunk Based Greedy Meshing and Perlin Noise Generation - ~25fps for 12x12x12 chunks rendered (post scene rendering optimization 6/04/2023)
    // With Chunk Based Greedy Meshing and Perlin Noise Generation - ~30fps ~1.5gb for 12x12x12 chunks rendered (post chunk byte size reduction 7/04/2023)

    // Implement LOD
    // Implement chunk loading
    // Make chunks use less data
}

void TestingScene::UpdateScene(float *deltaTimePtr) {

    int chunkViewDist = 1;

    //std::future<void> asyncA = std::async(std::launch::async, &VoxelWorld::UpdateChunks, voxelWorld, chunkViewDist, GetCamera()->GetPosition());

    // This allows the loading of new chunks based on viewers position
    //voxelWorld->UpdateChunks(chunkViewDist,Scene::GetCamera()->GetPosition());
}