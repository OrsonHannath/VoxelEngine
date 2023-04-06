//
// Created by User on 26/02/2023.
//

#include "Colour.h"

void Colour::SetRed(int red_) {

    red = red_;
}

void Colour::SetGreen(int green_) {

    green = green_;
}

void Colour::SetBlue(int blue_) {

    blue = blue_;
}

void Colour::SetAlpha(int alpha_) {

    alpha = alpha_;
}

void Colour::SetRGBA(int r, int g, int b, int a){

    red = r;
    green = g;
    blue = b;
    alpha = a;
}

int Colour::GetRed() {

    return red;
}

int Colour::GetGreen() {

    return green;
}

int Colour::GetBlue() {
     return blue;
}

int Colour::GetAlpha() {

    return alpha;
}

Colour Colour::operator*(Colour &col) const {

    return Colour((int)((red/255.0f) * (col.GetRed()/255.0f)) * 255, (int)((green/255.0f) * (col.GetGreen()/255.0f)) * 255, (int)((blue/255.0f) * (col.GetBlue()/255.0f)) * 255, (int)((alpha/255.0f) * (col.GetAlpha()/255.0f)) * 255);
}

ColourStruct Colour::GetColourStruct() {

    ColourStruct cs = {red, green, blue, alpha};
    return cs;
}