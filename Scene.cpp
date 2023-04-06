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

    // Now draw the render object vertices
    glDrawArrays(GL_TRIANGLES, 0, vertsToDraw);

    float timerA = 0;
    float timerB = 0;
    float timerC = 0;
    float timerD = 0;
    float timerE = 0;

    // Draw each chunk
    for(auto& kv : voxelWorld->GetChunksMap()){

        float timeNow = glfwGetTime();

        Chunk* chunk = kv.second;

        // Get the render object and check if it should be rendered
        RenderObject* renderObject = chunk->GetRenderObject();
        if(!renderObject->ShouldRender()){

            std::cerr << chunk->GetChunkName() << " shouldn't render" << std::endl;
            continue;
        }

        timerE += glfwGetTime() - timeNow;

        // Get the vertex and colour information from the object
        std::vector<VoxelVertexStruct>* object_vertex_buffer = renderObject->GetVoxelVertexBufferDataAddress();
        std::vector<ColourStruct>* object_colour_buffer = renderObject->GetVertexColourDataAddress();
        int vertsToDraw = renderObject->GetVertexBufferDataSize(); // Number of vertices should be drawn

        timerA += glfwGetTime() - timeNow;

        // Voxel Face Triangle Positional Debugging
        /*for(int i = 0; i < (object_vertex_buffer.size() / sizeof(vertexBuffer)) / 12; i++){

            float xTotal = 0;
            float yTotal = 0;
            float zTotal = 0;
            for(int j = 0; j < 12; j++){

                xTotal += object_vertex_buffer.at((i*12) + j).x;
                yTotal += object_vertex_buffer.at((i*12) + j).y;
                zTotal += object_vertex_buffer.at((i*12) + j).z;
            }

            //std::cout << "[" << xTotal/12.0f << ", " << yTotal/12.0f << ", " << zTotal/12.0f << "]" << std::endl;
        }*/

        // Voxel Vertices Debugging
        /*for(int i = 0; i < (object_vertex_buffer.size() / sizeof(vertexBuffer)); i++){

            std::cout << object_vertex_buffer[i].toString() << std::endl;
        }*/

        // Update the MVPMatrix and ModelMatrix
        renderObject->SetMVPMatrix(camera->GenerateMVPMatrix());
        mat4 mvpMat = renderObject->GetMVPMatrix();
        glUniformMatrix4fv(GLHandles["matrixID"], 1, GL_FALSE, &mvpMat[0][0]);

        timerB += glfwGetTime() - timeNow;

        // Set the vertex buffer
        glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
        glBufferData(GL_ARRAY_BUFFER, renderObject->GetVertexBufferDataSize() * sizeof(VoxelVertexStruct), &(*object_vertex_buffer)[0], GL_STATIC_DRAW);

        // Set the vertex colour buffer
        glBindBuffer(GL_ARRAY_BUFFER, colourBuffer);
        glBufferData(GL_ARRAY_BUFFER, renderObject->GetVertexColourDataSize() * sizeof(ColourStruct), &(*object_colour_buffer)[0], GL_STATIC_DRAW);

        timerC  += glfwGetTime() - timeNow;

        // 1st attribute buffer : vertices
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
        glVertexAttribPointer(
                0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
                3,                  // size
                GL_INT,             // type
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
                GL_INT,                           // type
                GL_FALSE,                         // normalized?
                0,                                // stride
                (void*)0                          // array buffer offset
        );

        //glDrawArrays(GL_LINES, 0, vertsToDraw);
        glDrawArrays(GL_TRIANGLES, 0, vertsToDraw);

        timerD += glfwGetTime() - timeNow;
    }

    //std::cout << timerE << " Timer before getting vertex and colour data" << std::endl;
    //std::cout << timerA << " Timer before calculating MVP Matrix" << std::endl;
    //std::cout << timerB << " Timer before setting buffers" << std::endl;
    //std::cout << timerC << " Timer before setting attribute buffers" << std::endl;
    //std::cout << timerD << " Timer after drawing" << std::endl << std::endl;
}

void Scene::UpdateVertexBuffer(int &vertsToDraw_) {

    // Go through the scenes objects and find all that are render-able and add them to the vertex_buffer
    std::vector<VertexStruct> vertex_buffer_vector;
    std::vector<ColourStruct> vertex_colour_vector;
    for(auto& kv : objectsMapByName){

        Object* object = kv.second;

        // Check if the object is a RenderObject
        if(object->GetIsRenderObject()){

            //std::cout << object->GetName() << std::endl;

            // Get the vertex and colour information from the object
            RenderObject* renderObject = static_cast<RenderObject*>(object);
            std::vector<VertexStruct> object_vertex_buffer = renderObject->GetVertexBufferData();
            std::vector<ColourStruct> object_colour_buffer = renderObject->GetVertexColourData();

            // Add the vertex and colour information to the total vectors
            vertex_buffer_vector.insert(vertex_buffer_vector.end(), object_vertex_buffer.begin(), object_vertex_buffer.end());
            vertex_colour_vector.insert(vertex_colour_vector.end(), object_colour_buffer.begin(), object_colour_buffer.end());

            // Update the MVPMatrix and ModelMatrix
            renderObject->SetMVPMatrix(camera->GenerateMVPMatrix());
            mat4 mvpMat = renderObject->GetMVPMatrix();
            glUniformMatrix4fv(GLHandles["matrixID"], 1, GL_FALSE, &mvpMat[0][0]);
        }
    }

    // Let the renderer know how many triangles need to be drawn
    int numVerts = vertex_buffer_vector.size() * 3;
    vertsToDraw_ = numVerts;

    // Give our vertices to OpenGL.
    // The following commands will talk about our 'vertexbuffer' buffer
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, vertex_buffer_vector.size() * sizeof(vertex_buffer_vector[0]), &vertex_buffer_vector[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, colourBuffer);
    glBufferData(GL_ARRAY_BUFFER, vertex_colour_vector.size() * sizeof(vertex_colour_vector[0]), &vertex_colour_vector[0], GL_STATIC_DRAW);
}