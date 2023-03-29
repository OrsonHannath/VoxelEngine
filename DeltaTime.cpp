//
// Created by User on 4/03/2023.
//

#include "DeltaTime.h"

// Returns current time
double CurrentTime(){

    return glfwGetTime();
}

// Calculates and Returns the difference in time between current time and stored time in seconds
float DeltaTime(double oldTime){

    return float(CurrentTime() - oldTime);
}
