//
// Created by User on 26/02/2023.
//

#ifndef VOXELENGINE_COLOR_H
#define VOXELENGINE_COLOR_H

#include "Structures.h"

class Colour {
private:
    float red;
    float green;
    float blue;
    float alpha;
public:
    Colour(float red_, float green_, float blue_, float alpha_) : red(red_), green(green_), blue(blue_), alpha(alpha_){};

    void SetRed(int red_);
    void SetGreen(int green_);
    void SetBlue(int blue_);
    void SetAlpha(int alpha_);
    void SetRGBA(int r, int g, int b, int a);

    float GetRed();
    float GetGreen();
    float GetBlue();
    float GetAlpha();

    Colour operator*(Colour &col) const;

    ColourStruct GetColourStruct();
};

Colour LerpBetweenColours(Colour* startCol, Colour* endCol, float lerpPos);


#endif //VOXELENGINE_COLOR_H
