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
    void ResetDrawingParticleIndex() //call this every frame (after drawing multiple line)
    {
        drawingParticleIndex = 0;
    }
    void DrawLine(Vector2 startPosition, Vector2 endPosition);
    void CreateLineParticles(int amount, int color);
    void ClearLines()
    {
        for (auto lineParticles : lines)
        {
            lineParticles->Destroy(); //TODO: include lineparticle
        }
        lines.clear();
    }
private:
    int drawingParticleIndex = 0;
    std::vector<class LineParticle *> lines;
    Vector2 lastDrawnLinePosition;
    Scene &scene;
};