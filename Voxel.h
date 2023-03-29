//
// Created by User on 27/03/2023.
//

#ifndef VOXELENGINE_VOXEL_H
#define VOXELENGINE_VOXEL_H

#include <glm/glm.hpp>

class Voxel {
private:
    glm::vec3 position;
    int voxelType = 0; // The type of voxel/block this is
    bool solid = true; // Whether the voxel is solid or not
public:
    Voxel(int voxelType_, bool solid_);
};


#endif //VOXELENGINE_VOXEL_H
