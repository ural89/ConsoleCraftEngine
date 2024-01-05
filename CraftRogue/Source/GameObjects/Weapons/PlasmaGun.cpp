#include "PlasmaGun.h"
#include "PlasmaBullet.h"
#include "Core/Scene.h"


void PlasmaGun::Init()
{

    isRenderable = false;

}

void PlasmaGun::Fire(Vector2 fireDirection)
{
    GetCurrentScene().AddGameObject(new PlasmaBullet(GetCurrentScene(), fireDirection), transform.Position);
};