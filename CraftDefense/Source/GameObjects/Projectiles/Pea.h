#pragma once
#include "Core/GameObject.h"

class Pea : public GameObject
{
public:
    Pea(class Scene &s, int lane);

    void Init() override;
    void Update(float deltaTime) override;
    void OnCollided(GameObject &other) override;
    void OnCollidedBorder(int border) override;

private:
    int lane;
    float speed = 25.f;
    float damage = 1.f;
};
