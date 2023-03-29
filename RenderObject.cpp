//
// Created by User on 26/03/2023.
//

#include "RenderObject.h"

RenderObject::RenderObject(std::string name) : Object(name, true) {

}

void RenderObject::SetMVPMatrix(mat4 mvp) {

    mvpMatrix = mvp;
}

void RenderObject::SetVertexBufferData(std::vector<GLfloat> data_) {

    vertex_buffer_data = data_;
}

void RenderObject::SetVertexColourData(std::vector<GLfloat> data_) {

    vertex_colour_data = data_;
}

void RenderObject::SetObjectColour(vec4 col_) {

    std::vector<float> colourDataVec;
    for(GLfloat f : vertex_buffer_data){

        colourDataVec.push_back(col_.x);
        colourDataVec.push_back(col_.y);
        colourDataVec.push_back(col_.z);
        colourDataVec.push_back(col_.w);
    }

    vertex_colour_data = colourDataVec;
}

vec3 RenderObject::GetObjectPosition() {

    return GetPosition();
}

vec3 RenderObject::GetObjectRotation() {

    return GetRotation();
}

vec3 RenderObject::GetObjectScale() {

    return GetScale();
}

mat4 RenderObject::GetMVPMatrix() {

    return mvpMatrix;
}

std::vector<GLfloat> RenderObject::GetVertexBufferData() {

    return vertex_buffer_data;
}

std::vector<float> RenderObject::GetVertexColourData() {

    return vertex_colour_data;
}