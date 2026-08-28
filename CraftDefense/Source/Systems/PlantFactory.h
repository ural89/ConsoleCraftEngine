#pragma once
#include "DefenseConfig.h"

class Plant;
class Scene;
class LaneGrid;
class SunManager;

namespace PlantFactory
{
    Plant *Create(PlantType type, Scene &scene, LaneGrid &grid, SunManager &sunManager);
}
