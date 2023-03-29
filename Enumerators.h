//
// Created by User on 3/03/2023.
//

#ifndef VOXELENGINE_ENUMERATORS_H
#define VOXELENGINE_ENUMERATORS_H

#include <string>

enum RenderType {Realtime, Saved};
enum CollisionPhysicsTypes {Brute, SweepNPrune, UniformGridSpacePartitioning, BoundingVolumeHierarchy};
enum GenerationTypes {Instant, Gradual};
enum ColourTypes {Random, Lerp, Specific};
enum PositionOrigin {TopLeft, TopRight, BotLeft, BotRight, Center};

std::string EnumToString(CollisionPhysicsTypes enum_);
std::string EnumToString(GenerationTypes enum_);
std::string EnumToString(ColourTypes enum_);

CollisionPhysicsTypes CollisionPhysicsStringToEnum(std::string str);
GenerationTypes GenerationTypeStringToEnum(std::string str);
ColourTypes ColourTypeStringToEnum(std::string str);

#endif //VOXELENGINE_ENUMERATORS_H
