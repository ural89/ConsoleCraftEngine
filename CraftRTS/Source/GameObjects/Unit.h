#pragma once

#include "Component/AI/AIMovement.h"
#include "GameObject.h"
class Unit : public GameObject {
public:
  Unit(class Scene &scene) : GameObject("Unit", scene) {}
  void Init() override {
    symbol = '8';
    sprite = {
            {1, 5, 5, 1},
            {1, 5, 5, 1},
            {1, 5, 5, 1}
        };
    auto aiMovementComponent = new AIMovement(*this);
    AddComponent(aiMovementComponent);
  }
};
