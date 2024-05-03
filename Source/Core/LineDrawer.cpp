#include "LineDrawer.h"
#include "Scene.h"

void LineDrawer::DrawLine(Vector2 startPosition, Vector2 endPosition)
{
    Vector2 direction = endPosition - startPosition;
    int length = direction.LengthInt();
    direction.Normalize();
    if (length < lines.size())
    {
        for (size_t i = 0; i < length; i++)
        {

            Vector2 newPosition = direction * i + startPosition;
            lastDrawnLinePosition = newPosition;
            if (drawingParticleIndex < lines.size())
            {
                lines[drawingParticleIndex]->transform.SetPosition(newPosition.X, newPosition.Y);
                lines[drawingParticleIndex]->isRenderable = true;
                drawingParticleIndex++;
            }
        }
        // debugUIPtr->text = "particle count: " + std::to_string(drawingParticleIndex);
        for (size_t i = drawingParticleIndex - 1; i < lines.size(); i++)
        {
            lines[i]->isRenderable = false;
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
        polygonLineParticle->isRenderable = false;
    }
}
