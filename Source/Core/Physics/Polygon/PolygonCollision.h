#pragma once
#include "../../../Core.h"
#include "Polygon.h"
#include <vector>
class GE_API PolygonCollision
{
public:
    PolygonCollision()
    {
    }
    void UpdateResolve(float deltaTime);
    void AddPolygon(Polygon *polygon)
    {

        polygons.push_back(polygon);
    }

    void RemovePolygon(Polygon *polygon)
    {
        polygons.erase(std::remove(polygons.begin(), polygons.end(), polygon), polygons.end());
    }

private:
    std::vector<Polygon *> polygons;
    float PointToLineDistance(const Vector2 &point, const Vector2 &lineStart, const Vector2 &lineEnd);
    void ResolveCollisionForClosedPolygons(Polygon *polygonA, Polygon *polygonB, float deltaTime, int particleIndex);
    void ResolveCollision(Polygon *polygonA, Polygon *polygonB, float deltaTime, float overlapDepth, int particleIndex);
    bool CheckCollisionForClosedPolygon(Polygon *polygonA, Polygon *polygonB, int &particleIndex);
    bool CheckCollisionForEdgeToPoint(Polygon *polygonA, Polygon *polgonB, float &overlapDepth, int &particleIndex);
    bool IntersectPolygons(Polygon *polygonA, Polygon *polygonB, Vector2 &collisionNormal, float &depth);
    void ProjectPolygonOntoAxis(Polygon *polygon, const Vector2 &axis, float &min, float &max);
};