#include "PolygonCollision.h"
#include <algorithm>
void PolygonCollision::UpdateResolve(float deltaTime)
{
    for (size_t i = 0; i < polygons.size(); ++i)
    {
        for (size_t j = i + 1; j < polygons.size(); ++j)
        {
            Polygon *polygonA = polygons[i];
            Polygon *polygonB = polygons[j];
            int particleIndex;
            float overlapDepth;
            if (polygonA->isClosed)
            {
                if (CheckCollisionForClosedPolygon(polygonA, polygonB, particleIndex)) // if polygon A is closed
                {
                    ResolveCollisionForClosedPolygons(polygonA, polygonB, deltaTime, particleIndex);
                }
            }
            else if (CheckCollisionForEdgeToPoint(polygonA, polygonB, overlapDepth, particleIndex))
            {
                ResolveCollision(polygonA, polygonB, deltaTime, overlapDepth, particleIndex);
            }
            if (polygonB->isClosed)
            {
                if (CheckCollisionForClosedPolygon(polygonB, polygonA, particleIndex)) // if polygon B is closed
                {
                    ResolveCollisionForClosedPolygons(polygonB, polygonA, deltaTime, particleIndex);
                }
            }
            else if (CheckCollisionForEdgeToPoint(polygonB, polygonA, overlapDepth, particleIndex))
            {
                ResolveCollision(polygonB, polygonA, deltaTime, overlapDepth, particleIndex);
            }
        }
    }
}

bool PolygonCollision::CheckCollisionForClosedPolygon(Polygon *polygonA, Polygon *polygonB, int &particleIndex) // point to polygon collision check
{
    int i, j, nvert = polygonA->particles.size();
    for (size_t p = 0; p < polygonB->particles.size(); p++) // checking every particle of B (as point) to polygonA's edges
    {
        Vector2 point = polygonB->particles[p]->transform.Position;
        bool c = false;
        for (int i = 0, j = nvert - 1; i < nvert; j = i++)
        {

            if (((polygonA->particles[i]->transform.Position.Y >= point.Y) != (polygonA->particles[j]->transform.Position.Y >= point.Y)) &&
                (point.X <= (polygonA->particles[j]->transform.Position.X - polygonA->particles[i]->transform.Position.X) *
                                    (point.Y - polygonA->particles[i]->transform.Position.Y) /
                                    (polygonA->particles[j]->transform.Position.Y - polygonA->particles[i]->transform.Position.Y) +
                                polygonA->particles[i]->transform.Position.X))
            {
                c = !c;
            }
        }
        //  std::cout << p << '\n';
        if (c)
        {
            particleIndex = p;
            return true;
        }
    }
    return false;
}
void PolygonCollision::ResolveCollision(Polygon *polygonA, Polygon *polygonB, float deltaTime, float overlapDepth, int particleIndex)
{
    //  std::cout << overlapDepth << '\n';

    polygonB->OnCollided(Vector2(0, -1 * overlapDepth), particleIndex);
}
bool PolygonCollision::CheckCollisionForEdgeToPoint(Polygon *polygonA, Polygon *polygonB, float &overlapDepth, int& particleIndex)
{
    for (size_t p = 0; p < polygonB->particles.size(); p++)
    {
        Vector2 particlePosition = polygonB->particles[p]->transform.Position;
        float minDistance = std::numeric_limits<float>::max();

        // Check against each edge of polygonA
        for (size_t i = 0; i < polygonA->edges.size(); i++)
        {
            Vector2 edgeStart = polygonA->particles[i]->transform.Position;
            Vector2 edgeEnd = polygonA->particles[(i + 1) % polygonA->particles.size()]->transform.Position;

            float distance = PointToLineDistance(particlePosition, edgeStart, edgeEnd);

            if (distance < 2)
            {

                minDistance = distance;
            }
        }

        // Adjust this threshold according to your needs
        if (minDistance < 2)
        {
            particleIndex = p;
            overlapDepth = minDistance;
            return true; // Collision detected
        }
    }

    return false; // No collision
}
float PolygonCollision::PointToLineDistance(const Vector2 &point, const Vector2 &lineStart, const Vector2 &lineEnd)
{
    Vector2 line = lineEnd - lineStart;
    Vector2 pointToLineStart = point - lineStart;

    float t = pointToLineStart.Dot(line) / (line.Length() * line.Length());
    t = std::clamp(t, 0.0f, 1.0f);

    Vector2 closestPoint = lineStart + line * t;

    return (point - closestPoint).Length();
}
void PolygonCollision::ResolveCollisionForClosedPolygons(Polygon *polygonA, Polygon *polygonB, float deltaTime, int particleIndex)
{

    Vector2 direction = polygonB->particles[particleIndex]->transform.Position - polygonA->GetCenter();
    direction.Normalize(); // TODO: magnitude is distance to line! and multiply with distance to line

    polygonB->OnCollided(direction * 10, particleIndex);
}
bool PolygonCollision::IntersectPolygons(Polygon *polygonA, Polygon *polygonB, Vector2 &collisionNormal, float &depth)
{

    return true; // is collided
}
void PolygonCollision::ProjectPolygonOntoAxis(Polygon *polygon, const Vector2 &axis, float &min, float &max)
{
}
