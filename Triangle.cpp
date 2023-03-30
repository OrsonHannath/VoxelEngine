//
// Created by User on 26/03/2023.
//

#include "Triangle.h"

Triangle::Triangle(std::string name, vec3 pos, vec3 rot, vec3 scale) : RenderObject(name) {

    SetPosition(pos);
    SetRotation(rot);
    SetScale(scale);

    // Determine the vertex positions
    VertexStruct v1 = {pos.x - (scale.x/2.0f), pos.y, 0.0f};
    VertexStruct v2 = {pos.x, pos.y + scale.y, 0.0f};
    VertexStruct v3 = {pos.x + (scale.x/2.0f), pos.y, 0.0f};
    std::vector<VertexStruct> triangle_vertex_buffer_data = {v1, v2, v3};

    vertex_buffer_data = triangle_vertex_buffer_data;
    vertex_buffer_size = sizeof(triangle_vertex_buffer_data)/sizeof(triangle_vertex_buffer_data[0]);
}
