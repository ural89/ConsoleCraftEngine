#include "LineDrawer.h"
#include "Scene.h"

void LineDrawer::DrawLine(Vector2 startPosition, Vector2 endPosition)
{
    Vector2 direction = endPosition - startPosition;
    int length = direction.LengthInt();
    if(length == 0) return;
    direction.Normalize();
    if (length < lines.size())
    {
        for (size_t i = 0; i < length; i++)
        {

            Vector2 newPosition = direction * i + startPosition;
            if (drawingParticleIndex < lines.size())
            {
                lines[drawingParticleIndex]->transform.SetPosition(newPosition.X, newPosition.Y);
                lines[drawingParticleIndex]->isRenderable = true;
                drawingParticleIndex++;
            }
        }
    }
}

void LineDrawer::CreateLineParticles(int amount, int color)
{
    for (size_t i = 0; i < amount; i++)
    {
        LineParticle *polygonLineParticle = new LineParticle(scene);
        lines.push_back(polygonLineParticle);
        scene.AddGameObject(polygonLineParticle);
        polygonLineParticle->overrideColor = color;
        polygonLineParticle->isRenderable = true;
    }
}
