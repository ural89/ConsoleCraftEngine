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
            if (moveDirection == Vector2(0, 0) || moveDirection.Length() < 0.1f)
            {
                m_CurrentPathCorner++;
            }
            moveDirection.Normalize();
            owner->transform.MovePosition(moveDirection.X * deltaTime * 5, moveDirection.Y * deltaTime * 5);
            
        }
        m_TimeElapsedSincePathUpdate += deltaTime;
        if (m_TimeElapsedSincePathUpdate > m_UpdatePathDuration)
        {
            UpdatePath();
            m_CurrentPathCorner = 0;
            m_TimeElapsedSincePathUpdate = 0;
        }
    }
}

void AIMovement::UpdatePath()
{
    PathNode ownerNode(owner->transform.Position.X, owner->transform.Position.Y);
    PathNode targetNode(m_TargetTransform->Position.X, m_TargetTransform->Position.Y);
    m_Path = owner->GetCurrentScene().pathfinder->FindPath(ownerNode, targetNode);
}
