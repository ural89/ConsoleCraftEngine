#include "DestructionEffectComponent.h"

// @TODO: The Component <-> GameObject relationship will need to change!!!
#include "Core/GameObject.h"

void DestructionEffectComponent::Init()
{
    // @TODO: Look into this!!!
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
