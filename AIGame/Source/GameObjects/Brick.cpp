#include "Brick.h"
void Brick::Init()
{
    sprite = {{2,2,2,2},
                {2,2,2,2},
                {2,2,2,2},
                {2,2,2,2},
                {2,2,2,2}};
    symbol = "#";
    transform.Size = Vector2(4, 6);
}
