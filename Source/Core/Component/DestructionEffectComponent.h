#pragma once

#include "Component.h"
class DestructionEffectComponent : public Component
{
public:
    DestructionEffectComponent(GameObject& owner) : Component(owner)
    {

    }
    void Init() override;
    void Update(float deltaTime) override;
    void StartEffect();
private:
    class ParticleSource* particleSource;    
};