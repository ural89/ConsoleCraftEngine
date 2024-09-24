#include "AIMovement.h"
#include "../../Core/GameObject.h"
#include "../../Core/Scene.h"
void AIMovement::Init()
{
    UpdatePath();
}
void AIMovement::Update(float deltaTime)
{
    if (m_TargetTransform != nullptr)
    {
        if (m_Path.size() > m_CurrentPathCorner + 2)
        {
            Vector2 moveDirection = (Vector2(m_Path[m_CurrentPathCorner + 1].x, m_Path[m_CurrentPathCorner + 1].y) - owner->transform.Position);
            if (moveDirection == Vector2(0, 0) || moveDirection.Length() < 1.f)
            {
                m_CurrentPathCorner++;
            }
            moveDirection.Normalize();
            owner->transform.MovePosition(moveDirection.X * deltaTime * m_MoveSpeed, moveDirection.Y * deltaTime * m_MoveSpeed);
        }
        m_TimeElapsedSincePathUpdate += deltaTime;
        if (m_TimeElapsedSincePathUpdate > m_UpdatePathDuration)
        {
            if (m_TargetLastPosition != m_TargetTransform->Position)
            {
                UpdatePath();
                m_CurrentPathCorner = 0;
                m_TimeElapsedSincePathUpdate = 0;
            }
            m_TargetLastPosition = m_TargetTransform->Position;
        }
    }
    
}

void AIMovement::UpdatePath()
{
    PathNode ownerNode(owner->transform.Position.X, owner->transform.Position.Y);
    PathNode targetNode(m_TargetTransform->GetCenterPosition().X, m_TargetTransform->GetCenterPosition().Y);
    m_Path = owner->GetCurrentScene().pathfinder->FindPath(ownerNode, targetNode);
}
