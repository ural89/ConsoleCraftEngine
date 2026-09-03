#pragma once
#include "CoreStructs/Vector.h"
#include <string>

struct LevelData
{
    std::string name;

    float leftCliffX;  // right edge of the left plateau
    float rightCliffX; // left edge of the right plateau
    float groundY;      // deck / plateau surface height

    int deckSegments;
    float budget;

    bool hasPillar;
    float pillarX;
    float pillarTopY; // top surface of the mid-gap island; below groundY

    float startX;  // vehicle spawn X, on the left plateau
    float finishX; // X the vehicle must cross to win
};
