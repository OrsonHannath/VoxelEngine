//
// Created by User on 26/03/2023.
//

#ifndef VOXELENGINE_TESTINGSCENE_H
#define VOXELENGINE_TESTINGSCENE_H

#include <iostream>
#include "Scene.h"
#include "Triangle.h"
#include "Cube.h"
#include <cmath>
#include "ColourRandomizer.h"
#include "Colour.h"
#include "Chunk.h"
#include "VoxelWorld.h"

class TestingScene: public Scene {
public:
    TestingScene(std::string name, GLFWwindow* window_, std::map<std::string, GLuint> GLHandles_);

    void UpdateScene(float *deltaTimePtr);
};


#endif //VOXELENGINE_TESTINGSCENE_H
