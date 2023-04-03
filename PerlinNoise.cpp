//
// Created by User on 30/03/2023.
//

#include "PerlinNoise.h"

PerlinNoise::PerlinNoise() {

}

// https://www.youtube.com/watch?v=SoakEoUQ7Rg
float PerlinNoise::GetNoiseAtPoint(int x, int y, int z) {

    glm::vec3 point = glm::vec3(x*frequency, y*frequency, z*frequency);

    int flooredPointX0 = floor(point.x);
    int flooredPointY0 = floor(point.y);
    int flooredPointZ0 = floor(point.z);

    float distanceX0 = point.x - flooredPointX0;
    float distanceY0 = point.y - flooredPointY0;
    float distanceZ0 = point.z - flooredPointZ0;

    float distanceX1 = distanceX0 - 1.0f;
    float distanceY1 = distanceY0 - 1.0f;
    float distanceZ1 = distanceZ0 - 1.0f;

    flooredPointX0 &= permutationCount;
    flooredPointY0 &= permutationCount;
    flooredPointZ0 &= permutationCount;

    int flooredPointX1 = flooredPointX0 + 1;
    int flooredPointY1 = flooredPointY0 + 1;
    int flooredPointZ1 = flooredPointZ0 + 1;

    int permutationX0 = permutation[flooredPointX0];
    int permutationX1 = permutation[flooredPointX1];

    int permutationY00 = permutation[permutationX0 + flooredPointY0];
    int permutationY10 = permutation[permutationX1 + flooredPointY0];
    int permutationY01 = permutation[permutationX0 + flooredPointY1];
    int permutationY11 = permutation[permutationX1 + flooredPointY1];

    glm::vec3 direction000 = directions[permutation[permutationY00 + flooredPointZ0] & directionCount];
    glm::vec3 direction100 = directions[permutation[permutationY10 + flooredPointZ0] & directionCount];
    glm::vec3 direction010 = directions[permutation[permutationY01 + flooredPointZ0] & directionCount];
    glm::vec3 direction110 = directions[permutation[permutationY11 + flooredPointZ0] & directionCount];
    glm::vec3 direction001 = directions[permutation[permutationY00 + flooredPointZ1] & directionCount];
    glm::vec3 direction101 = directions[permutation[permutationY10 + flooredPointZ1] & directionCount];
    glm::vec3 direction011 = directions[permutation[permutationY01 + flooredPointZ1] & directionCount];
    glm::vec3 direction111 = directions[permutation[permutationY11 + flooredPointZ1] & directionCount];

    float value000 = Scalar(direction000, glm::vec3(distanceX0, distanceY0, distanceZ0));
    float value100 = Scalar(direction100, glm::vec3(distanceX1, distanceY0, distanceZ0));
    float value010 = Scalar(direction010, glm::vec3(distanceX0, distanceY1, distanceZ0));
    float value110 = Scalar(direction110, glm::vec3(distanceX1, distanceY1, distanceZ0));
    float value001 = Scalar(direction001, glm::vec3(distanceX0, distanceY0, distanceZ1));
    float value101 = Scalar(direction101, glm::vec3(distanceX1, distanceY0, distanceZ1));
    float value011 = Scalar(direction011, glm::vec3(distanceX0, distanceY1, distanceZ1));
    float value111 = Scalar(direction111, glm::vec3(distanceX1, distanceY1, distanceZ1));

    float smoothDistanceX = SmoothDistance(distanceX0);
    float smoothDistanceY = SmoothDistance(distanceY0);
    float smoothDistanceZ = SmoothDistance(distanceZ0);

    return Lerp(
            Lerp(Lerp(value000, value100, smoothDistanceX), Lerp(value010, value110, smoothDistanceX), smoothDistanceY),
            Lerp(Lerp(value001, value101, smoothDistanceX), Lerp(value011, value111, smoothDistanceX), smoothDistanceY),
            smoothDistanceZ);
}

int PerlinNoise::GetPermutationCount() {

    return permutationCount;
}

float PerlinNoise::Scalar(glm::vec3 a, glm::vec3 b) {

    return a.x * b.x + a.y * b.y + a.z * b.z;
}

float PerlinNoise::SmoothDistance(float d) {

    return d * d * d * (d * (d * 6.0f - 15.0f) + 10.0f);
}

float PerlinNoise::Lerp(float a, float b, float t) {

    return a * (1.0f - t) + (b * t);
}

