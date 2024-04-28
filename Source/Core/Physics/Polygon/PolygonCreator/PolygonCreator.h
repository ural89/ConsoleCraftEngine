#pragma once
#include "../../../../Core.h"
#include "../../../../CoreStructs/Vector.h"
#include "PolygonCursor.h"
#include <memory>
class GE_API PolygonCreator //Created polygons' owner ship is moved to scene!!!
{
public:
    PolygonCreator(class Scene& scene);
    ~PolygonCreator()
    {
        delete cursor; 
        cursor = nullptr;
    }
    class Polygon* ApplyAndGetPolygon();

    void StartCreating(Vector2 position);
    void SetPosition(Vector2 position);
    void CreateSquarePolygon(Vector2 position, int size, float rotationAngle);
    void CreateRectanglePolygon(Transform transform);
    void CreateCircle(Vector2 position, float radius, int numSegments);
private:
    Polygon* currentPolygon;
    Scene& scene;

    class Cursor* cursor;
    
    bool isCreating = false;
    int particleIndex = 0;
    
    void OnInput(int input);
};
