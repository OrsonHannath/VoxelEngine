//
// Created by User on 26/02/2023.
//

#ifndef VOXELENGINE_COLOR_H
#define VOXELENGINE_COLOR_H

#include "Structures.h"

class Colour {
private:
    int red;
    int green;
    int blue;
    int alpha;
public:
    Colour(int red_, int green_, int blue_, int alpha_) : red(red_), green(green_), blue(blue_), alpha(alpha_){};

    void SetRed(int red_);
    void SetGreen(int green_);
    void SetBlue(int blue_);
    void SetAlpha(int alpha_);
    void SetRGBA(int r, int g, int b, int a);

    int GetRed();
    int GetGreen();
    int GetBlue();
    int GetAlpha();

    Colour operator*(Colour &col) const;

    ColourStruct GetColourStruct();
};


#endif //VOXELENGINE_COLOR_H
