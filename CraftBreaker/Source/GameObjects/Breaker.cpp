#include "Breaker.h"
#include "Core/Component/PlayerController.h"
void Breaker::Init()
{
    AddComponent(new PlayerController(*this, 0));
    sprite = {
        {3,3,3,3,3,3}
    };
    symbol = '#';
}