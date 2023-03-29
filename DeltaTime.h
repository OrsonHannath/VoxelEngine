//
// Created by User on 27/02/2023.
//

#ifndef VOXELENGINE_DELTATIME_H
#define VOXELENGINE_DELTATIME_H

#include <glfw3.h>

// Returns current time
double CurrentTime();

// Calculates and Returns the difference in time between current time and stored time in seconds
float DeltaTime(double oldTime);

#endif //VOXELENGINE_DELTATIME_H
