//
// Created by User on 26/03/2023.
//

#ifndef VOXELENGINE_SCENE_H
#define VOXELENGINE_SCENE_H


#include <iostream>
#include <map>
#include <glew.h>
#include <vector>
#include <cmath>
#include <memory>
#include "Camera.h"
#include "Object.h"
#include "RenderObject.h"
#include "Chunk.h"
#include "VoxelWorld.h"

class Scene {
protected:
    std::map<std::string, GLuint> GLHandles;
    VoxelWorld* voxelWorld;
private:
    std::string name;
    Camera* camera;
    GLuint vertexBuffer;
    GLuint colourBuffer;
    GLFWwindow* window;

    void UpdateVertexBuffer(int &vertsToDraw_);

protected:
    std::map<std::string, Object*> objectsMapByName;
    std::map<std::string, Object*> chunkRenderObjectsMapByName;
public:

    Scene(std::string name_, GLFWwindow* window_, std::map<std::string, GLuint> GLHandles_);
    void RenderScene(float* deltaTimePtr);

    void SetCamera(Camera* cam);
    void SetGLHandle(std::string handleStr_, GLuint handleVal_);

    Camera* GetCamera();
    std::string GetName();
};


#endif //VOXELENGINE_SCENE_H
