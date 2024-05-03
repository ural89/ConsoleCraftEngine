#pragma once

class RoadCreator
{
public:
    RoadCreator(class Scene& scene, class PolygonCreator& polygonCreator);
    void CreateRoad(int amount, class Vector2 startPosition, Vector2 endPosition);

private:
    Scene& scene;
    class PolygonCreator& polygonCreator;
};