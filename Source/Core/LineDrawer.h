#pragma once
#include <vector>
#include "../CoreStructs/Vector.h"
#include "Physics/Polygon/LineParticle.h"
class LineDrawer
{
public:
    LineDrawer(class Scene &scene) : scene(scene)
    {
    }
    ~LineDrawer()
    {
        lines.clear();
    }
    void ResetDrawingParticleIndex() // call this every frame (after drawing multiple line)
    {
        for (size_t i = drawingParticleIndex; i < lines.size(); i++)
        {
            if (!lines[i]->isRenderable)
                continue;
            lines[i]->SetRenderable(false);
        }
        drawingParticleIndex = 0;
    }
    void DrawLine(Vector2 startPosition, Vector2 endPosition);
    void CreateLineParticles(int amount, int color);
    void ClearLines()
    {
        for (auto lineParticles : lines)
        {
            lineParticles->Destroy(); // TODO: include lineparticle
        }
        lines.clear();
    }
    int drawingParticleIndex = 0;

private:
    std::vector<class LineParticle *> lines;
    Vector2 lastDrawnLinePosition;
    Scene &scene;
};