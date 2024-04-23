#include "BlastGun.h"
#include "PlasmaBullet.h"
#include "Core/Scene.h"
void BlastGun::Init()
{
    isRenderable = false;
}

void BlastGun::Fire(GameObject &targetGameObject)
{
   

    for (int i = 0; i < numberOfBullets; i++)
    {
        double randomAngle = static_cast<double>(rand()) / RAND_MAX * 2 * 3.14f;

        double speed = 25.0;
        double randomDirectionX = speed * std::cos(randomAngle);
        double randomDirectionY = speed * std::sin(randomAngle);

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
