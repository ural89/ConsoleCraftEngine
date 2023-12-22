#include "Collision.h"


void Collision::AddGameObject(GameObject* gameObject) 
{
	gameObjects.push_back(gameObject);

}

void Collision::RemoveGameObject(GameObject* gameObject)
{
    auto newEnd = std::remove(gameObjects.begin(), gameObjects.end(), gameObject); //Move element to last
    gameObjects.erase(newEnd, gameObjects.end()); //erase last one
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


Collision::~Collision()
{
	gameObjects.clear();
}
