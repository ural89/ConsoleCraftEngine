#include "BlastGun.h"
#include "PlasmaBullet.h"
#include "Graphics/Scene.h"

void BlastGun::Init()
{
    isRenderable = false;
}

void BlastGun::Fire(GameObject &targetGameObject)
{
   

    for (int i = 0; i < numberOfBullets; i++)
    {
        float randomAngle = static_cast<float>(rand()) / (float)RAND_MAX * 2.0f * 3.14f;

        float speed = 25.0;
        float randomDirectionX = speed * std::cos(randomAngle);
        float randomDirectionY = speed * std::sin(randomAngle);

        Vector2 randomDirection(randomDirectionX, randomDirectionY);
        randomDirection.Normalize();
        auto plasmaBullet = new PlasmaBullet(GetCurrentScene(), randomDirection, damage);
        plasmaBullet->sprite = {
            {3,1},
            {1,3}
        };
        GetCurrentScene().AddGameObject(plasmaBullet, transform.Position);
    }
}
