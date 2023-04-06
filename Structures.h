//
// Created by User on 28/03/2023.
//

#ifndef VOXELENGINE_STRUCTURES_H
#define VOXELENGINE_STRUCTURES_H

#include <glm/glm.hpp>
#include <iostream>

struct ChunkStruct{
    glm::ivec3 pos;
};

struct VoxelStruct{
    int voxType;
    int isSolid;
};

struct VoxelVertexStruct{
    int x;
    int y;
    int z;

    bool operator==(VoxelVertexStruct &vertex) const{

        return (x == vertex.x) && (y == vertex.y) && (z == vertex.z);
    }

    std::string toString(){

        std::string str = "[" + std::to_string(x) + ", " + std::to_string(y) + ", "+ std::to_string(z) + "]";
        return str;
    }
};

struct VertexStruct{
    float x;
    float y;
    float z;

    bool operator==(VertexStruct &vertex) const{

        return (x == vertex.x) && (y == vertex.y) && (z == vertex.z);
    }

    std::string toString(){

        std::string str = "[" + std::to_string(x) + ", " + std::to_string(y) + ", "+ std::to_string(z) + "]";
        return str;
    }
};

struct ColourStruct{
    int r;
    int g;
    int b;
    int a;

    ColourStruct operator*(ColourStruct &colour) const{

        ColourStruct cs = {(int)((r/255.0f) * (colour.r/255.0f)) * 255, (int)((g/255.0f) * (colour.g/255.0f)) * 255, (int)((b/255.0f) * (colour.b/255.0f)) * 255, (int)((a/255.0f) * (colour.a/255.0f)) * 255};
        return cs;
    }

    ColourStruct operator+(ColourStruct &colour) const{

        ColourStruct cs = {r + colour.r, g + colour.g, b + colour.b, a + colour.a};
        return cs;
    }
};


#endif //VOXELENGINE_STRUCTURES_H
