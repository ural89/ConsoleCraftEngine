#include "DestructionEffectComponent.h"
#include "../ParticleSystem/ParticleSource.h"
#include "../GameObject.h"
#include "../../CoreStructs/Vector.h"

void DestructionEffectComponent::Init()
{
    particleSource = new ParticleSource(*owner);
}

void DestructionEffectComponent::Update(float deltaTime)
{
}

void DestructionEffectComponent::StartEffect()
{
    for (int j = 0; j < owner->GetHeight(); j++) {
    for (int i = 0; i < owner->GetWidth(); i++) {
        owner->sprite[j][i] = 0;
        particleSource->EmitParticle(1, BRICKPARTICLE, Vector2(i, j)); //TODO: give color of the owner
    }
    }

    
}
