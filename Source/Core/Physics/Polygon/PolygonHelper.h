#pragma once
#include <vector>
#include "PolygonParticle.h"
#include "../../../CoreStructs/Vector.h"
#include "../../GameObject.h"

static Vector2 GetCenterPointWorldPosition(std::vector<PolygonParticle *> &vertices)
{
    int vertexCount = vertices.size();
    Vector2 centroid = {0, 0};
    double signedArea = 0.0;
    double x0 = 0.0; // Current vertex X
    double y0 = 0.0; // Current vertex Y
    double x1 = 0.0; // Next vertex X
    double y1 = 0.0; // Next vertex Y
    double a = 0.0;  // Partial signed area

    // For all vertices except last
    int i = 0;
    for (i = 0; i < vertexCount - 1; ++i)
    {
        x0 = vertices[i]->transform.Position.X;
        y0 = vertices[i]->transform.Position.Y;
        x1 = vertices[i + 1]->transform.Position.X;
        y1 = vertices[i + 1]->transform.Position.Y;
        a = x0 * y1 - x1 * y0;
        signedArea += a;
        centroid.X += (x0 + x1) * a;
        centroid.Y += (y0 + y1) * a;
    }

    // Do last vertex separately to avoid performing an expensive
    // modulus operation in each iteration.
    x0 = vertices[i]->transform.Position.X;
    y0 = vertices[i]->transform.Position.Y;
    x1 = vertices[0]->transform.Position.X;
    y1 = vertices[0]->transform.Position.Y;
    a = x0 * y1 - x1 * y0;
    signedArea += a;
    centroid.X += (x0 + x1) * a;
    centroid.Y += (y0 + y1) * a;

    signedArea *= 0.5;
    centroid.X /= (6.0 * signedArea);
    centroid.Y /= (6.0 * signedArea);

    return centroid;
}