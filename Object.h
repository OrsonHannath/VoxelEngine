//
// Created by User on 26/03/2023.
//

#ifndef VOXELENGINE_OBJECT_H
#define VOXELENGINE_OBJECT_H

#include <glm/vec3.hpp>
#include "iostream"

using namespace glm;

class Object {
private:
    bool isRenderObject = false;
protected:

    std::string name;
    vec3 position;
    vec3 rotation;
    vec3 scale;
public:

    Object(std::string name_);
    Object(std::string name_, bool isRenderObject_);

    void SetName(std::string name_);
    void SetPosition(vec3 position_);
    void SetRotation(vec3 rotation_);
    void SetScale(vec3 scale_);

    std::string GetName();
    vec3 GetPosition();
    vec3 GetRotation();
    vec3 GetScale();

    bool GetIsRenderObject();
};


#endif //VOXELENGINE_OBJECT_H
