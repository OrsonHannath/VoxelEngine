//
// Created by User on 26/03/2023.
//

#ifndef VOXELENGINE_RENDEROBJECT_H
#define VOXELENGINE_RENDEROBJECT_H


#include <glm/gtc/matrix_transform.hpp>
#include <glew.h>
#include <vector>
#include "Object.h"

class RenderObject: public Object{
protected:
    std::vector<GLfloat> vertex_buffer_data;
    std::vector<GLfloat> vertex_colour_data;
    int vertex_buffer_size;
    mat4 modelMatrix;
    mat4 mvpMatrix;
public:
    RenderObject(std::string name);

    void SetMVPMatrix(mat4 mvp);
    void SetObjectColour(vec4 col_);
    void SetVertexBufferData(std::vector<GLfloat> data_);
    void SetVertexColourData(std::vector<GLfloat> data_);


    vec3 GetObjectPosition();
    vec3 GetObjectRotation();
    vec3 GetObjectScale();
    mat4 GetMVPMatrix();
    std::vector<GLfloat> GetVertexBufferData();
    std::vector<float> GetVertexColourData();
};


#endif //VOXELENGINE_RENDEROBJECT_H
