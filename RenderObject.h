//
// Created by User on 26/03/2023.
//

#ifndef VOXELENGINE_RENDEROBJECT_H
#define VOXELENGINE_RENDEROBJECT_H


#include <glm/gtc/matrix_transform.hpp>
#include <glew.h>
#include <vector>
#include "Structures.h"
#include "Colour.h"
#include "Object.h"

class RenderObject: public Object{
protected:
    std::vector<VertexStruct> vertex_buffer_data;
    std::vector<ColourStruct> vertex_colour_data;
    int vertex_buffer_size;
    mat4 modelMatrix;
    mat4 mvpMatrix;
    bool shouldRender = true;
public:
    RenderObject(std::string name);

    void SetMVPMatrix(mat4 mvp);
    void SetObjectColour(ColourStruct col_);
    void SetVertexBufferData(std::vector<VertexStruct> data_);
    void SetVertexColourData(std::vector<ColourStruct> data_);

    void OverlayVertexColours(Colour col);
    void SetShouldRender(bool shouldRender_);

    bool ShouldRender();
    vec3 GetObjectPosition();
    vec3 GetObjectRotation();
    vec3 GetObjectScale();
    mat4 GetMVPMatrix();
    int GetVertexBufferDataSize();
    int GetVertexColourDataSize();
    std::vector<VertexStruct> GetVertexBufferData();
    std::vector<ColourStruct> GetVertexColourData();
    std::vector<VertexStruct>* GetVertexBufferDataAddress();
    std::vector<ColourStruct>* GetVertexColourDataAddress();
};


#endif //VOXELENGINE_RENDEROBJECT_H
