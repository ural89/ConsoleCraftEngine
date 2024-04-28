#include "DemolishHandler.h"
#include "../GameObjects/Buildings/Buildable.h"
#include "../CityStatics/CityStatics.h"

void DemolishHandler::Demolish(GameObject &buildable)
{
    if (auto building = static_cast<Buildable *>(&buildable))
    {
        
        building->IsDemolishFlag = true;
    }
}