#pragma once
#include "../../Core.h"
#include "Component.h"
class GE_API DestructionEffectComponent : public Component
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