//
// Created by User on 23/03/2023.
//

#ifndef VOXELENGINE_OPENGLAPP_H
#define VOXELENGINE_OPENGLAPP_H

#include <iostream>
#include <cstdio>
#include <glew.h>
#include <glfw3.h>
#include <glm/glm.hpp>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include "DeltaTime.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Object.h"
#include "Triangle.h"
#include "TestingScene.h"

class OpenGLApp {
public:
    OpenGLApp();

    int OnExecute(int width, int height);
    bool OnInit();
    void OnLoop();
    void OnRender();
    void OnExit();

    GLuint* LoadShaders(const char* vertex_file_path, const char* fragment_file_path, const char* compute_file_path);

private:

    bool isRunning;
    GLuint programID;
    GLuint computeProgramID;
    GLuint matrixID;

    // Window Settings
    GLFWwindow* window;
    int wWidth;
    int wHeight;

    // Time management
    float deltaTime;
    double time_;

    // Scene management
    SceneManager* sceneManager;
};


#endif //VOXELENGINE_OPENGLAPP_H
