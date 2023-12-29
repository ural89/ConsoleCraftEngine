#include "Breaker.h"
#include "Core/Component/PlayerController.h"
void Breaker::Init()
{
    AddComponent(new PlayerController(*this, 0));
    sprite = {
        {1,1,1,1,1,1}
    };
    symbol = '#';
}