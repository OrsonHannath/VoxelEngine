//
// Created by User on 27/03/2023.
//

#include "Cube.h"

Cube::Cube(std::string name, vec3 pos, vec3 rot, vec3 scale) : RenderObject(name) {

    SetPosition(pos);
    SetRotation(rot);
    SetScale(scale);

    float halfScaleX = scale.x/2.0;
    float halfScaleY = scale.y/2.0;
    float halfScaleZ = scale.z/2.0;

    // https://en.wikibooks.org/wiki/OpenGL_Programming/Modern_OpenGL_Tutorial_05#:~:text=A%20cube%20is%208%20vertices,can%20be%20renamed%20to%20cube%20.
    // Determine the vertex positions two tris per cube face
    VertexStruct v0 = {pos.x - halfScaleX, pos.y - halfScaleY, pos.z + halfScaleZ}; // Front
    VertexStruct v1 = {pos.x + halfScaleX, pos.y - halfScaleY, pos.z + halfScaleZ}; // Front
    VertexStruct v2 = {pos.x + halfScaleX, pos.y + halfScaleY, pos.z + halfScaleZ}; // Front
    VertexStruct v3 = {pos.x - halfScaleX, pos.y + halfScaleY, pos.z + halfScaleZ}; // Front
    VertexStruct v4 = {pos.x - halfScaleX, pos.y - halfScaleY, pos.z - halfScaleZ}; // Back
    VertexStruct v5 = {pos.x + halfScaleX, pos.y - halfScaleY, pos.z - halfScaleZ}; // Back
    VertexStruct v6 = {pos.x + halfScaleX, pos.y + halfScaleY, pos.z - halfScaleZ}; // Back
    VertexStruct v7 = {pos.x - halfScaleX, pos.y + halfScaleY, pos.z - halfScaleZ}; // Back

    std::vector<VertexStruct> triangle_vertex_buffer_data = {
            v0, v1, v2, // Front
            v2, v3, v0, // Front
            v1, v5, v6, // Right
            v6, v2, v1, // Right
            v7, v6, v5, // Back
            v5, v4, v7, // Back
            v4, v0, v3, // Left
            v3, v7, v4, // Left
            v4, v5, v1, // Bottom
            v1, v0, v4, // Bottom
            v3, v2, v6, // Top
            v6, v7, v3 // Top
    };

    vertex_buffer_data = triangle_vertex_buffer_data;
    vertex_buffer_size = sizeof(triangle_vertex_buffer_data)/sizeof(triangle_vertex_buffer_data[0]);
}

void Cube::SetVertexColours(std::vector<ColourStruct> vertexColours) {

    vertex_colour_data = vertexColours;
}