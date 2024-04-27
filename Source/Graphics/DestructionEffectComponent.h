#pragma once

#include "Graphics/ParticleSystem/ParticleSource.h"

class DestructionEffectComponent : public Component
{
public:
    void Init() override;
    void Update(float deltaTime) override;
    void StartEffect();

    DestructionEffectComponent(GameObject& owner) : Component(owner) {}

private:
    ParticleSource* particleSource = nullptr;    
};