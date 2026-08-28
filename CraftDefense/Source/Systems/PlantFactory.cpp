#include "PlantFactory.h"
#include "GameObjects/Plants/Sunflower.h"
#include "GameObjects/Plants/Peashooter.h"
#include "GameObjects/Plants/Wallnut.h"

Plant *PlantFactory::Create(PlantType type, Scene &scene, LaneGrid &grid, SunManager &sunManager)
{
    switch (type)
    {
    case PlantType::Sunflower:
        return new Sunflower(scene, grid, sunManager);
    case PlantType::Peashooter:
        return new Peashooter(scene, grid);
    case PlantType::Wallnut:
        return new Wallnut(scene, grid);
    }
    return nullptr;
}
