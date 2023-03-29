//
// Created by User on 3/03/2023.
//

#include "Enumerators.h"

enum RenderType;
enum CollisionPhysicsTypes;
enum GenerationTypes;
enum ColourTypes;
enum PositionOrigin;

std::string EnumToString(CollisionPhysicsTypes enum_){

    switch (enum_) {
        case Brute:
            return "Brute";
        case SweepNPrune:
            return "SweepNPrune";
        case UniformGridSpacePartitioning:
            return "UniformGridSpacePartitioning";
        case BoundingVolumeHierarchy:
            return "BoundingVolumeHierarchy";
    }

    return "NULL";
}

std::string EnumToString(GenerationTypes enum_){

    switch (enum_) {
        case Instant:
            return "Instant";
        case Gradual:
            return "Gradual";
    }

    return "NULL";
}

std::string EnumToString(ColourTypes enum_){

    switch (enum_) {
        case Random:
            return "Random";
        case Lerp:
            return "Lerp";
        case Specific:
            return "Specific";
    }

    return "NULL";
}

CollisionPhysicsTypes CollisionPhysicsStringToEnum(std::string str){

    if(str == "Brute"){
        return Brute;
    }else if(str == "SweepNPrune"){
        return SweepNPrune;
    }
    else if(str == "UniformGridSpacePartitioning"){
        return UniformGridSpacePartitioning;
    }
    else if(str == "BoundingVolumeHierarchy"){
        return BoundingVolumeHierarchy;
    }

    return static_cast<CollisionPhysicsTypes>(NULL);
}

GenerationTypes GenerationTypeStringToEnum(std::string str){

    if(str == "Instant"){
        return Instant;
    }else if(str == "Gradual"){
        return Gradual;
    }

    return static_cast<GenerationTypes>(NULL);
}

ColourTypes ColourTypeStringToEnum(std::string str){

    if(str == "Random"){
        return Random;
    }else if(str == "Lerp"){
        return Lerp;
    }
    else if(str == "Specific"){
        return Specific;
    }

    return static_cast<ColourTypes>(NULL);
}