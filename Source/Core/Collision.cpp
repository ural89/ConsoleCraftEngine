#include "Collision.h"
#include <algorithm>

void Collision::AddGameObject(GameObject* gameObject) 
{
	gameObjects.push_back(gameObject);

}

void Collision::RemoveGameObject(GameObject* gameObject)
{
    gameObjects.erase(std::remove(gameObjects.begin(), gameObjects.end(), gameObject), gameObjects.end());
}

void Collision::CheckForCollisions() const
{
    for (size_t i = 0; i < gameObjects.size(); ++i)
    {
        for (size_t j = i + 1; j < gameObjects.size(); ++j)
        {
            auto first = gameObjects[i];
            auto second = gameObjects[j];

          
            if (
                first->transform.Position.X < second->transform.Position.X + second->GetWidth() &&
                second->transform.Position.X < first->transform.Position.X + first->GetWidth() &&
                first->transform.Position.Y < second->transform.Position.Y + second->GetHeight() &&
                second->transform.Position.Y < first->transform.Position.Y + first->GetHeight()
                )
            {
             
                first->OnCollided(*second);
                second->OnCollided(*first);
            }
        }
    }
}

void Collision::CheckForBorderCollisions() const
{
    for (auto& go : gameObjects)
    {

        if (go->transform.Position.X + 1>= SCREENWIDTH || go->transform.Position.X -1 <= 0) go->OnCollidedBorder();
        if (go->transform.Position.Y + 1 >= SCREENHEIGHT || go->transform.Position.Y -1 <= 0) go->OnCollidedBorder();

    }
}


Collision::~Collision()
{
	gameObjects.clear();
}
