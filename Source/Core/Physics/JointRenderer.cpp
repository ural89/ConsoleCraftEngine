#include "JointRenderer.h"
#include "../LineDrawer.h"
#include "../Scene.h"
JointRenderer::JointRenderer(Scene &scene) : scene(scene)
{
    lineDrawer = new LineDrawer(scene);
    int color = 1;
    lineDrawer->CreateLineParticles(100, color);
}
JointRenderer::~JointRenderer()
{
    delete lineDrawer;
    lineDrawer = nullptr;
}
void JointRenderer::Update(float deltaTime)
{
    lineDrawer->ResetDrawingParticleIndex();
    for (b2Joint *joint = scene.World->GetJointList(); joint; joint = joint->GetNext())
    {
        b2Vec2 anchorA = joint->GetAnchorA();
        b2Vec2 anchorB = joint->GetAnchorB();

        Vector2 startPosition(anchorA.x, anchorA.y);
        Vector2 endPosition(anchorB.x, anchorB.y);

        lineDrawer->DrawLine(startPosition, endPosition);
    }
}
