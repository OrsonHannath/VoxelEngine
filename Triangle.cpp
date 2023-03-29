//
// Created by User on 26/03/2023.
//

#include "Triangle.h"

Triangle::Triangle(std::string name, vec3 pos, vec3 rot, vec3 scale) : RenderObject(name) {

    SetPosition(pos);
    SetRotation(rot);
    SetScale(scale);

    // Determine the vertex positions
    vec3 v1 = vec3(pos.x - (scale.x/2.0f), pos.y, 0.0f);
    vec3 v2 = vec3(pos.x, pos.y + scale.y, 0.0f);
    vec3 v3 = vec3(pos.x + (scale.x/2.0f), pos.y, 0.0f);

    std::vector<GLfloat> triangle_vertex_buffer_data = {v1.x, v1.y, v1.z, v2.x, v2.y, v2.z, v3.x, v3.y, v3.z};

    vertex_buffer_data = triangle_vertex_buffer_data;
    vertex_buffer_size = sizeof(triangle_vertex_buffer_data)/sizeof(triangle_vertex_buffer_data[0]);
}
