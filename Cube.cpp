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
    vec3 v0 = vec3(pos.x - halfScaleX, pos.y - halfScaleY, pos.z + halfScaleZ); // Front
    vec3 v1 = vec3(pos.x + halfScaleX, pos.y - halfScaleY, pos.z + halfScaleZ); // Front
    vec3 v2 = vec3(pos.x + halfScaleX, pos.y + halfScaleY, pos.z + halfScaleZ); // Front
    vec3 v3 = vec3(pos.x - halfScaleX, pos.y + halfScaleY, pos.z + halfScaleZ); // Front
    vec3 v4 = vec3(pos.x - halfScaleX, pos.y - halfScaleY, pos.z - halfScaleZ); // Back
    vec3 v5 = vec3(pos.x + halfScaleX, pos.y - halfScaleY, pos.z - halfScaleZ); // Back
    vec3 v6 = vec3(pos.x + halfScaleX, pos.y + halfScaleY, pos.z - halfScaleZ); // Back
    vec3 v7 = vec3(pos.x - halfScaleX, pos.y + halfScaleY, pos.z - halfScaleZ); // Back

    std::vector<GLfloat> triangle_vertex_buffer_data = {
            v0.x, v0.y, v0.z, v1.x, v1.y, v1.z, v2.x, v2.y, v2.z, // Front
            v2.x, v2.y, v2.z, v3.x, v3.y, v3.z, v0.x, v0.y, v0.z, // Front
            v1.x, v1.y, v1.z, v5.x, v5.y, v5.z, v6.x, v6.y, v6.z, // Right
            v6.x, v6.y, v6.z, v2.x, v2.y, v2.z, v1.x, v1.y, v1.z, // Right
            v7.x, v7.y, v7.z, v6.x, v6.y, v6.z, v5.x, v5.y, v5.z, // Back
            v5.x, v5.y, v5.z, v4.x, v4.y, v4.z, v7.x, v7.y, v7.z, // Back
            v4.x, v4.y, v4.z, v0.x, v0.y, v0.z, v3.x, v3.y, v3.z, // Left
            v3.x, v3.y, v3.z, v7.x, v7.y, v7.z, v4.x, v4.y, v4.z, // Left
            v4.x, v4.y, v4.z, v5.x, v5.y, v5.z, v1.x, v1.y, v1.z, // Bottom
            v1.x, v1.y, v1.z, v0.x, v0.y, v0.z, v4.x, v4.y, v4.z, // Bottom
            v3.x, v3.y, v3.z, v2.x, v2.y, v2.z, v6.x, v6.y, v6.z, // Top
            v6.x, v6.y, v6.z, v7.x, v7.y, v7.z, v3.x, v3.y, v3.z // Top
    };

    vertex_buffer_data = triangle_vertex_buffer_data;
    vertex_buffer_size = sizeof(triangle_vertex_buffer_data)/sizeof(triangle_vertex_buffer_data[0]);
}

void Cube::SetVertexColours(std::vector<float> vertexColours) {

    vertex_colour_data = vertexColours;
}