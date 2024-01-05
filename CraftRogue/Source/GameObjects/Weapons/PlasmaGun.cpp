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
    Vector2 StartPoint = transform.Position;
    auto nearestEnemy = GetCurrentScene().GetNearestGameObject(transform, "Enemy");
    if (nearestEnemy != nullptr)
    {
        Vector2 TargetPoint = nearestEnemy->transform.Position;

        Vector2 FireDirection = TargetPoint - StartPoint;
        FireDirection.Normalize();
        if (input == SPACEBAR)
            Fire(FireDirection);
    }
}
void PlasmaGun::Fire(Vector2 fireDirection)
{
    GetCurrentScene().AddGameObject(new Bullet(GetCurrentScene(), fireDirection), transform.Position);
};