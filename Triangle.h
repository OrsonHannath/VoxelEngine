//
// Created by User on 26/03/2023.
//

#ifndef VOXELENGINE_TRIANGLE_H
#define VOXELENGINE_TRIANGLE_H


#include <glm/vec3.hpp>
#include "RenderObject.h"

class Triangle: public RenderObject {
public:
    Triangle(std::string name, vec3 pos, vec3 rot, vec3 scale);
};


#endif //VOXELENGINE_TRIANGLE_H
