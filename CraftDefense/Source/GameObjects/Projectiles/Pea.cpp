#include "Pea.h"
#include "GameObjects/Zombies/Zombie.h"

Pea::Pea(Scene &s, int lane)
    : GameObject("Pea", s), lane(lane)
{
}

void Pea::Init()
{
    symbol = "*";
    overrideColor = 2;
    Sprite sprite = {
        {1},
    };
    SetSprite(sprite);
}

void Pea::Update(float deltaTime)
{
    transform.MovePosition(speed * deltaTime, 0);
}

void Pea::OnCollided(GameObject &other)
{
    if (other.name != "Zombie")
        return;

    Zombie *zombie = dynamic_cast<Zombie *>(&other);
    if (zombie && zombie->Lane() == lane)
    {
        zombie->TakeDamage(1.f);
        Destroy();
    }
}

void Pea::OnCollidedBorder(int border)
{
    Destroy();
}
