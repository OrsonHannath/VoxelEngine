//
// Created by User on 26/03/2023.
//

#include "RenderObject.h"

RenderObject::RenderObject(std::string name) : Object(name, true) {

}

void RenderObject::SetMVPMatrix(mat4 mvp) {

    mvpMatrix = mvp;
}

void RenderObject::SetVertexBufferData(std::vector<VertexStruct> data_) {

    vertex_buffer_data = data_;
}

void RenderObject::SetVoxelVertexBufferData(std::vector<VoxelVertexStruct> data_) {

    voxel_vertex_buffer_data = data_;
}

void RenderObject::SetVertexColourData(std::vector<ColourStruct> data_) {

    vertex_colour_data = data_;
}

void RenderObject::OverlayVertexColours(Colour col) {

    std::vector<ColourStruct> colourDataVec;
    for(ColourStruct cs : vertex_colour_data){

        ColourStruct multi = col.GetColourStruct();
        ColourStruct newCS = cs * multi;
        colourDataVec.push_back(newCS);
    }

    vertex_colour_data = colourDataVec;
}

void RenderObject::SetObjectColour(ColourStruct col_) {

    std::vector<ColourStruct> colourDataVec;

    // Check if we are rendering a voxel or something else
    if(voxel_vertex_buffer_data.size() > 0){

        for(VoxelVertexStruct vs : voxel_vertex_buffer_data){

            ColourStruct cs = {col_.r, col_.g, col_.b, col_.a};
            colourDataVec.push_back(cs);
        }
    }else{

        for(VertexStruct vs : vertex_buffer_data){

            ColourStruct cs = {col_.r, col_.g, col_.b, col_.a};
            colourDataVec.push_back(cs);
        }
    }

    vertex_colour_data = colourDataVec;
}

void RenderObject::SetShouldRender(bool shouldRender_) {

    shouldRender = shouldRender_;
}

bool RenderObject::ShouldRender() {

    return shouldRender;
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

int RenderObject::GetVertexBufferDataSize() {

    if(voxel_vertex_buffer_data.size() > 0){

        return voxel_vertex_buffer_data.size();
    }else {

        return vertex_buffer_data.size();
    }
}

int RenderObject::GetVertexColourDataSize() {

    return vertex_colour_data.size();
}

std::vector<VertexStruct> RenderObject::GetVertexBufferData() {

    return vertex_buffer_data;
}

std::vector<VertexStruct>* RenderObject::GetVertexBufferDataAddress() {

    return &vertex_buffer_data;
}

std::vector<VoxelVertexStruct> RenderObject::GetVoxelVertexBufferData() {

    return voxel_vertex_buffer_data;
}

std::vector<VoxelVertexStruct>* RenderObject::GetVoxelVertexBufferDataAddress() {

    return &voxel_vertex_buffer_data;
}

std::vector<ColourStruct> RenderObject::GetVertexColourData() {

    return vertex_colour_data;
}

std::vector<ColourStruct>* RenderObject::GetVertexColourDataAddress() {

    return &vertex_colour_data;
}