//
// Created by User on 26/03/2023.
//

#include "Scene.h"

Scene::Scene(std::string name_, GLFWwindow* window_, std::map<std::string, GLuint> GLHandles_) {

    name = name_;
    window = window_;
    GLHandles = GLHandles_;

    int winWidth, winHeight;
    glfwGetWindowSize(window, &winWidth, &winHeight);

    // Generate buffers, put the resulting identifier in vertexbuffer, colourBuffer
    glGenBuffers(1, &vertexBuffer);
    glGenBuffers(1, &colourBuffer);
}

void Scene::SetCamera(Camera *cam) {

    camera = cam;
}

void Scene::SetGLHandle(std::string handleStr_, GLuint handleVal_) {

    GLHandles[handleStr_] = handleVal_;
}

Camera* Scene::GetCamera() {

    return camera;
}

std::string Scene::GetName(){

    return name;
}

void Scene::RenderScene(float* deltaTimePtr) {

    // Update the Camera
    camera->UpdateCamera(deltaTimePtr);

    // Update the Vertex Buffer
    int vertsToDraw = 0;
    UpdateVertexBuffer(vertsToDraw);

    // Let OpenGL to use our shader
    glUseProgram(GLHandles["programID"]);

    // 1st attribute buffer : vertices
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glVertexAttribPointer(
            0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
            3,                  // size
            GL_FLOAT,           // type
            GL_FALSE,           // normalized?
            0,                  // stride
            (void*)0            // array buffer offset
    );

    // 2nd attribute buffer : colors
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, colourBuffer);
    glVertexAttribPointer(
            1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
            4,                                // size
            GL_FLOAT,                         // type
            GL_FALSE,                         // normalized?
            0,                                // stride
            (void*)0                          // array buffer offset
    );

    // Draw the triangles/faces
    glDrawArrays(GL_TRIANGLES, 0, vertsToDraw); // Starting from vertex 0; 3 vertices total -> 1 triangle
    glDisableVertexAttribArray(0);
}

void Scene::UpdateVertexBuffer(int &vertsToDraw_) {

    // Go through the scenes objects and find all that are render-able and add them to the vertex_buffer
    std::vector<GLfloat> vertex_buffer_vector;
    std::vector<GLfloat> vertex_colour_vector;
    for(auto& kv : objectsMapByName){

        Object* object = kv.second;

        // Check if the object is a RenderObject
        if(object->GetIsRenderObject()){

            //std::cout << object->GetName() << std::endl;

            RenderObject* renderObject = static_cast<RenderObject*>(object);
            std::vector<GLfloat> object_vertex_buffer = renderObject->GetVertexBufferData();
            std::vector<float> object_colour_buffer = renderObject->GetVertexColourData();

            for(GLfloat val : object_vertex_buffer){

                vertex_buffer_vector.push_back(val);
            }

            for(GLfloat val : object_colour_buffer){

                vertex_colour_vector.push_back(val);
            }

            // Update the MVPMatrix and ModelMatrix
            renderObject->SetMVPMatrix(camera->GenerateMVPMatrix());
            mat4 mvpMat = renderObject->GetMVPMatrix();
            glUniformMatrix4fv(GLHandles["matrixID"], 1, GL_FALSE, &mvpMat[0][0]);
        }
    }

    // Let the renderer know how many triangles need to be drawn
    int numVerts = vertex_buffer_vector.size();
    vertsToDraw_ = numVerts;

    // Give our vertices to OpenGL.
    // The following commands will talk about our 'vertexbuffer' buffer
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, vertex_buffer_vector.size() * sizeof(vertex_buffer_vector[0]), &vertex_buffer_vector[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, colourBuffer);
    glBufferData(GL_ARRAY_BUFFER, vertex_colour_vector.size() * sizeof(vertex_colour_vector[0]), &vertex_colour_vector[0], GL_STATIC_DRAW);
}