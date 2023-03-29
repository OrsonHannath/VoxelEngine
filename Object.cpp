//
// Created by User on 26/03/2023.
//

#include "Object.h"


Object::Object(std::string name_) {

    name = name_;
}

Object::Object(std::string name_, bool isRenderObject_) {

    name = name_;
    isRenderObject = isRenderObject_;
}

void Object::SetName(std::string name_) {

    name = name_;
}

void Object::SetPosition(vec3 position_) {

    position = position_;
}

void Object::SetRotation(vec3 rotation_) {

    rotation = rotation_;
}

void Object::SetScale(vec3 scale_) {

    scale = scale_;
}

std::string Object::GetName() {

    return name;
}

vec3 Object::GetPosition() {

    return position;
}

vec3 Object::GetRotation() {

    return rotation;
}

vec3 Object::GetScale() {

    return scale;
}

bool Object::GetIsRenderObject() {

    return isRenderObject;
}