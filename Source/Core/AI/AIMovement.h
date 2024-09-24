#pragma once
#include "../../CoreStructs/Transform.h"
#include "Pathfinder.h"
#include "../../Core/Component/Component.h"
class AIMovement : public Component
{
public:
    AIMovement(GameObject& gameObject) : Component(gameObject)
    {

    }

    void SetTargetTransform(const Transform* transform)
    {
        m_TargetTransform = transform;
    }
    void Init() override;
    void Update(float deltaTime) override;


private:
    float m_MoveSpeed = 3;
    float m_TimeElapsedSincePathUpdate = 0;
    float m_UpdatePathDuration = 1;
    int m_CurrentPathCorner = 0;

private:
    const Transform *m_TargetTransform;
    std::vector<PathNode> m_Path;
private:
    void UpdatePath();
};