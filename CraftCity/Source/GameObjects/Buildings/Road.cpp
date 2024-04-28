#include "Road.h"
#include "Core/Scene.h"
#include "BuildingTrigger.h"
void Road::Init()
{
    Buildable::Init();
    symbol = '=';
    buildingTrigger = new BuildingTrigger(scene, Vector2(GetWidth() * 2, GetHeight() * 2), *this);
    scene.AddGameObject(buildingTrigger, transform.Position - Vector2(GetWidth() / 2, GetHeight() / 2));
}

void Road::OnInfrastructureConnected(InfrastructureType infrastructureType)
{
    overrideColor = GREEN;
}

void Road::OnInfrastructureDisconnected(InfrastructureType infrastructureType)
{
    overrideColor = RED;
}

