#include "Collision.h"
#include <algorithm>

void Collision::AddGameObject(GameObject *gameObject)
{
    gameObjects.push_back(gameObject);
}

void Collision::RemoveGameObject(GameObject *gameObject)
{
    // Remove the object from the game objects list
    gameObjects.erase(std::remove(gameObjects.begin(), gameObjects.end(), gameObject), gameObjects.end());

    // Find and remove colliding pairs involving the removed object
    for (auto it = collidingPairs.begin(); it != collidingPairs.end();)
    {
        if (it->first == gameObject || it->second == gameObject)
        {
            // Call OnCollisionExit for the other object in the pair
            if (it->first != gameObject)
            {
                it->first->OnCollisionExit(*gameObject);
            }
            else
            {
                it->second->OnCollisionExit(*gameObject);
            }
            it = collidingPairs.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

void Collision::CheckForCollisions()
{

    for (size_t i = 0; i < gameObjects.size(); ++i)
    {
        for (size_t j = i + 1; j < gameObjects.size(); ++j)
        {
            auto first = gameObjects[i];
            auto second = gameObjects[j];

            if (first->transform.HasMovedThisFrame || second->transform.HasMovedThisFrame)
            {
                bool isColliding =
                    first->transform.Position.X < second->transform.Position.X + second->GetWidth() &&
                    second->transform.Position.X < first->transform.Position.X + first->GetWidth() &&
                    first->transform.Position.Y < second->transform.Position.Y + second->GetHeight() &&
                    second->transform.Position.Y < first->transform.Position.Y + first->GetHeight();

                auto it = collidingPairs.find(std::make_pair(first, second));
                // if(it != collidingPairs.end())
                // {
                //     if(first->isDestroyedFlag)
                //     {
                //         second->OnCollisionExit(*first);
                //         collidingPairs.erase(it);
                //         return;
                //     }
                //     else if(second->isDestroyedFlag)
                //     {
                //         first->OnCollisionExit(*second);
                //         collidingPairs.erase(it);
                //         return;
                //     }
                // }
                // Enter collision
                if (isColliding && it == collidingPairs.end())
                {
                    first->OnCollided(*second);
                    second->OnCollided(*first);
                    collidingPairs.insert(std::make_pair(first, second));
                }
                else if (!isColliding && it != collidingPairs.end())
                {
                    // Exit collision
                    first->OnCollisionExit(*second);
                    second->OnCollisionExit(*first);
                    collidingPairs.erase(it);
                }
            }
        }
    }
}
void Collision::CheckForBorderCollisions() const // trigger like
{
    for (auto &go : gameObjects)
    {

        if (go->transform.Position.X + 1 >= SCREENWIDTH)
            go->OnCollidedBorder(RIGHTBORDER);
        if (go->transform.Position.X - 1 <= 0)
            go->OnCollidedBorder(LEFTBORDER);
        if (go->transform.Position.Y + 1 >= SCREENHEIGHT)
            go->OnCollidedBorder(BOTTOMBORDER);
        if (go->transform.Position.Y - 1 <= 0)
            go->OnCollidedBorder(TOPBORDER);
    }
}

GameObject* Collision::GetCollidedObject(Vector2 position)
{
    // Iterate through all game objects
    for (auto& gameObject : gameObjects)
    {
        // Check if the provided position falls within the bounds of the current game object
        if (position.X >= gameObject->transform.Position.X &&
            position.X <= gameObject->transform.Position.X + gameObject->GetWidth() &&
            position.Y >= gameObject->transform.Position.Y &&
            position.Y <= gameObject->transform.Position.Y + gameObject->GetHeight())
        {
            // If the position is within the bounds of this game object, return it
            return gameObject;
        }
    }

    // If no game object is found at the given position, return nullptr
    return nullptr;
}

Collision::~Collision() { gameObjects.clear(); }
