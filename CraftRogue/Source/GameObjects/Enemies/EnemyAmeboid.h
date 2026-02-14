#pragma once
#include "EnemyRogue.h"

class EnemyAmeboid : public EnemyRogue
{
public:
    EnemyAmeboid(class Scene& scene) : EnemyRogue(scene)
    {

    }
    void Init() override;
    void Update(float deltaTime) override;
    void OnMove() override;
private:
    std::vector<Sprite> sprites;
    std::vector<std::string> symbols;
    int animationIndex = 0;
};
