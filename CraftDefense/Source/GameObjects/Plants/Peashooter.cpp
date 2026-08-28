#include "Peashooter.h"
#include "Grid/LaneGrid.h"
#include "GameObjects/Projectiles/Pea.h"
#include "Core/Scene.h"

Peashooter::Peashooter(Scene &s, LaneGrid &grid)
    : Plant("Peashooter", s, grid, 4.f)
{
}

void Peashooter::Init()
{
    Plant::Init();
    symbol = "o";
    overrideColor = 2; // green
    Sprite sprite = {
        {0, 1, 0},
        {1, 1, 1},
    };
    SetSprite(sprite);
}

void Peashooter::Update(float deltaTime)
{
    fireTimer += deltaTime;
    if (fireTimer < FIRE_INTERVAL)
        return;

    float muzzleX = transform.Position.X + GetWidth();
    if (!grid.FirstZombieAheadOf(Row(), muzzleX))
        return;

    fireTimer = 0.f;
    Pea *pea = new Pea(GetCurrentScene(), Row());
    GetCurrentScene().AddGameObject(pea, Vector2(muzzleX, transform.Position.Y + 1));
}
