#include "SelectCursor.h"

void SelectCursor::SetSize(Vector2 size, char &&symbol)
{
    this->symbol = symbol;
    this->size = size;
    transform.HasClearedFlag = false;
    transform.HasMovedThisFrame = true;
    // transform.MovePosition(-1,0);
    // transform.MovePosition(1,0);
    for (size_t i = 0; i < sprite.size(); i++)
    {
        for (size_t j = 0; j < sprite[i].size(); j++)
        {
            sprite[i][j] = 0; // Set all elements to 0
        }
    }
    for (size_t i = 0; i < size.Y; i++)
    {
        for (size_t j = 0; j < size.X; j++)
        {
            if (i == 0 || j == size.X - 1 || j == 0 || i == size.Y - 1)
                sprite[i][j] = 1;
        }
    }

    overrideColor = 2;
}

void SelectCursor::OnCollided(GameObject &other)
{
    if (other.name == "Trigger")
        return;
    collidedObject = &other;
    /// collidedObject->overrideColor = 1;
    overrideColor = RED;
    CanBuild = false;
}

void SelectCursor::OnCollisionExit(GameObject &other)
{
    
    if (collidedObject)
    {
        if (collidedObject == &other || collidedObject->isDestroyedFlag)
        {
            overrideColor = GREEN;
            CanBuild = true;
            collidedObject = nullptr;
        }
    }
}

void SelectCursor::Update(float deltaTime)
{
}
