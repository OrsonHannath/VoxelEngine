//
// Created by User on 26/03/2023.
//

#include <glew.h>
#include "Camera.h"

Camera::Camera(vec3 position_, GLFWwindow* window_) {

    window = window_;
    position = position_;

    float deltT = 0;
    UpdateCamera(&deltT);
}

Camera::Camera(vec3 position_, float horizontalAngle_, float verticalAngle_, GLFWwindow *window_) {

    position = position_;
    horizontalAngle = horizontalAngle_;
    verticalAngle = verticalAngle_;
    window = window_;

    float deltT = 0;
    UpdateCamera(&deltT);
}

Camera::Camera(vec3 position_, int FoV_, GLFWwindow *window_) {

    position = position_;
    fov = FoV_;
    window = window_;

    float deltT = 0;
    UpdateCamera(&deltT);
}

Camera::Camera(vec3 position_, int FoV_, float speed_, float mouseSpeed_, GLFWwindow *window_) {

    position = position_;
    fov = FoV_;
    speed = speed_;
    mouseSpeed = mouseSpeed_;
    window = window_;

    float deltT = 0;
    UpdateCamera(&deltT);
}

mat4 Camera::GenerateMVPMatrix() {

    // Model matrix : an identity matrix (model will be at the origin)
    glm::mat4 Model = glm::mat4(1.0f);

    // Our ModelViewProjection : multiplication of our 3 matrices
    glm::mat4 mvp = projection * view * Model; // Remember, matrix multiplication is the other way around

    return mvp;
}

void Camera::UpdateCamera(float* deltaTimePtr) {

    // Get the current window size
    int windowWidth;
    int windowHeight;
    glfwGetWindowSize(window, &windowWidth, &windowHeight);

    // Update the mouse position
    double mouseX, mouseY;
    glfwGetCursorPos(window, &mouseX, &mouseY);

    // Reset mouse position for next frame
    glfwSetCursorPos(window, windowWidth/2.0, windowHeight/2.0);

    // Compute new orientation
    horizontalAngle += (mouseSpeed * *deltaTimePtr) * float(windowWidth/2 - mouseX);
    verticalAngle += (mouseSpeed * *deltaTimePtr) * float(windowHeight/2 - mouseY);

    // Direction : Spherical coordinates to Cartesian coordinates conversion
    glm::vec3 direction(
            cos(verticalAngle) * sin(horizontalAngle),
            sin(verticalAngle),
            cos(verticalAngle) * cos(horizontalAngle)
    );

    // Right vector
    glm::vec3 right = glm::vec3(
            sin(horizontalAngle - 3.14f/2.0f),
            0,
            cos(horizontalAngle - 3.14f/2.0f)
    );

    // Up vector : perpendicular to both direction and right
    glm::vec3 up = glm::cross( right, direction );

    // Move forward
    if (glfwGetKey(window, GLFW_KEY_W ) == GLFW_PRESS){
        position += direction * *deltaTimePtr * speed;
    }
    // Move backward
    if (glfwGetKey(window, GLFW_KEY_S ) == GLFW_PRESS){
        position -= direction * *deltaTimePtr * speed;
    }
    // Strafe right
    if (glfwGetKey(window, GLFW_KEY_D ) == GLFW_PRESS){
        position += right * *deltaTimePtr * speed;
    }
    // Strafe left
    if (glfwGetKey(window, GLFW_KEY_A ) == GLFW_PRESS){
        position -= right * *deltaTimePtr * speed;
    }

    // Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
    projection = glm::perspective(glm::radians((float)fov), (float) windowWidth / (float)windowHeight, 0.1f, 100.0f);

    // Camera matrix
    view = glm::lookAt(
            position, // Camera is at (4,3,3), in World Space
            position + direction, // and looks at the origin
            up  // Head is up (set to 0,-1,0 to look upside-down)
    );
}

void Camera::SetPosition(vec3 pos) {

    position = pos;
}

void Camera::SetFOV(int fov_) {

    fov = fov_;
}

void Camera::SetHorizontalAngle(float horizontalAngle_) {

    horizontalAngle = horizontalAngle_;
}

void Camera::SetVerticalAngle(float verticalAngle_) {

    verticalAngle = verticalAngle_;
}

void Camera::SetSpeed(float speed_) {

    speed = speed_;
}

void Camera::SetMouseSpeed(float mouseSpeed_) {

    mouseSpeed = mouseSpeed_;
}
