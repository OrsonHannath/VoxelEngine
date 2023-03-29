//
// Created by User on 27/02/2023.
//

#include "Random.h"

// Produces a random integer in the specified range
int RandomInt(int startRange, int endRange){

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(startRange, endRange);

    return dis(gen);
}

// Produces a random float with X decimals (upto 6) in the specified range
float RandomFloat(float startRange, float endRange, int decimals){

    int startRangeScaled = startRange * pow(10, decimals);
    int endRangeScaled = endRange * pow(10, decimals);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(startRangeScaled, endRangeScaled);

    float randFloat = (dis(gen)) / pow(10, decimals);
    return randFloat;
}
