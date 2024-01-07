#include "WaveGun.h"
#include "../../Components/Health.h"
#include "Core/ParticleSystem/ParticleSource.h"
void WaveGun::Init()
{
    AddComponent(new ParticleSource(*this));
}

void WaveGun::Update(float deltaTime)
{
    if (targetGameObject != nullptr)
    {
        fireDuration += deltaTime;
        if (targetGameObject->transform.HasOwnerDestroyed)
        {
            targetGameObject = nullptr;
            StopWeapon();
        }
        else
        {
            if (fireDuration >= 1)
            {
                targetGameObject->GetComponent<Health>()->GiveDamage(1);
                fireDuration = 0;
            }
        }
    }
}

void WaveGun::Fire(GameObject &targetGameObject)
{
    this->targetGameObject = &targetGameObject;
    GetComponent<ParticleSource>()->EmitWaveParticle(targetGameObject.transform, Vector2(0, 0));
}

void WaveGun::StopWeapon()
{
    GetComponent<ParticleSource>()->ClearWaveParticles();
    
}
