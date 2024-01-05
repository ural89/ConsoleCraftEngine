#include "PlasmaGun.h"
#include "Bullet.h"
#include "Core/Scene.h"
#include "Core/Input.h"

void PlasmaGun::Init()
{
   
    isRenderable = false;
    auto inputEvent = std::bind(&PlasmaGun::OnKeyPressed, this, std::placeholders::_1);
    Input::AddListener(inputEvent);
}
void PlasmaGun::OnKeyPressed(int input)
{
    if (input == SPACEBAR)
        Fire(Vector2(1, 0));
}
void PlasmaGun::Fire(Vector2 fireDirection)
{
    GetCurrentScene().AddGameObject(new Bullet(GetCurrentScene()), transform.Position);
};