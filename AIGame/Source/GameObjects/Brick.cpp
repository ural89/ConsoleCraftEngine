#include "Brick.h"
void Brick::Init()
{
    Sprite sprite = {{2,2,2,2},
                {2,2,2,2},
                {2,2,2,2},
                {2,2,2,2},
                {2,2,2,2}};
    symbol = "#";
    SetSprite(sprite);
    transform.Size = Vector2(4, 6);
}
