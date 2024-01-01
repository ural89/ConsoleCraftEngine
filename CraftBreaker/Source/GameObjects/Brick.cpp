#include "Brick.h"
#include "Core/Component/DestructionEffectComponent.h"
void Brick::Init()
{
    destructionEffectComponent = new DestructionEffectComponent(*this);
    AddComponent(destructionEffectComponent);
    sprite = {{2,2,2,2},
                {2,2,2,2},
                {2,2,2,2}};
    symbol = "#";
}

void Brick::OnCollided(const GameObject &other)
{
    if(other.name == "Ball")
    {
        destructionEffectComponent->StartEffect();
    Destroy();
    }
}