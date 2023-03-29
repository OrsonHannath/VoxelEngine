//
// Created by User on 27/02/2023.
//

#include "ColourRandomizer.h"

Colour RandomColour(){

    return {RandomFloat(0, 1, 6), RandomFloat(0, 1, 6), RandomFloat(0, 1, 6), 1};
}
