#include "SunToken.h"

SunToken::SunToken(Scene &s, int col, int row)
    : GameObject("SunToken", s), col(col), row(row)
{
}

void SunToken::Init()
{
    hasCollider = false;
    symbol = "*";
    overrideColor = 3;
    Sprite sprite = {
        {1},
    };
    SetSprite(sprite);
}

void SunToken::Update(float deltaTime)
{
    lifeTimer += deltaTime;
    if (lifeTimer >= LIFETIME)
        Destroy();
}
