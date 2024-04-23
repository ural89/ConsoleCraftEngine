#include "PlasmaGun.h"
#include "PlasmaBullet.h"
#include "Core/Scene.h"

void PlasmaGun::Init()
{

    isRenderable = false;
}

void PlasmaGun::Fire(GameObject &targetGameObject)
{
    Vector2 fireDirection = targetGameObject.transform.Position - transform.Position;
    fireDirection.Normalize();
    GetCurrentScene().AddGameObject(new PlasmaBullet(GetCurrentScene(), fireDirection, damage), transform.Position);
}