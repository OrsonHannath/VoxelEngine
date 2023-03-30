//
// Created by User on 26/03/2023.
//

#ifndef VOXELENGINE_CAMERA_H
#define VOXELENGINE_CAMERA_H

#include <iostream>
#include <glm/vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "libraries/GLFW/glfw3.h"

using namespace glm;

class Camera {
private:
    vec3 position = vec3(0, 0, 5);
    float horizontalAngle = 3.14f;
    float verticalAngle = 0.0f;
    int fov = 60;
    float speed = 10.0f;
    float mouseSpeed = 0.5f;

    mat4 projection;
    mat4 view;

    GLFWwindow* window;
public:

    Camera(vec3 position_, GLFWwindow* window_);
    Camera(vec3 position_, float horizontalAngle_, float verticalAngle_, GLFWwindow* window_);
    Camera(vec3 position_, int FoV_, GLFWwindow* window_);
    Camera(vec3 position_, int FoV_, float speed_, float mouseSpeed_, GLFWwindow* window_);
    glm::mat4 GenerateMVPMatrix();

    void SetPosition(vec3 pos);
    void SetFOV(int fov_);
    void SetHorizontalAngle(float horizontalAngle_);
    void SetVerticalAngle(float verticalAngle_);
    void SetSpeed(float speed_);
    void SetMouseSpeed(float mouseSpeed_);
    void UpdateCamera(float* deltaTimePtr);
};


#endif //VOXELENGINE_CAMERA_H
