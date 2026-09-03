#include "BuildCursor.h"

BuildCursor::BuildCursor(Scene &scene) : GameObject("BuildCursor", scene)
{
}

void BuildCursor::Init()
{
    hasCollider = false;
    canFindable = false;
    isNavIgnore = true;
    symbol = "+";
    overrideColor = GREEN;

    Sprite sprite = {{1}};
    SetSprite(sprite);
}

void BuildCursor::SetBounds(float newMinX, float newMaxX, float newMinY, float newMaxY)
{
    minX = newMinX;
    maxX = newMaxX;
    minY = newMinY;
    maxY = newMaxY;
}

void BuildCursor::Move(float dx, float dy)
{
    float x = transform.Position.X + dx;
    float y = transform.Position.Y + dy;

    if (x < minX) x = minX;
    if (x > maxX) x = maxX;
    if (y < minY) y = minY;
    if (y > maxY) y = maxY;

    transform.SetPosition(x, y);
}
