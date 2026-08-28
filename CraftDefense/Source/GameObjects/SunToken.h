#pragma once
#include "Core/GameObject.h"

class SunToken : public GameObject
{
public:
    SunToken(class Scene &s, int col, int row);

    void Init() override;
    void Update(float deltaTime) override;

    int Col() const { return col; }
    int Row() const { return row; }

private:
    int col;
    int row;
    float lifeTimer = 0.f;
    static constexpr float LIFETIME = 15.f;
};
