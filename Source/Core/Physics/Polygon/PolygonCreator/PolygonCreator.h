#pragma once
#include "../../../../Core.h"
#include "../../../../CoreStructs/Vector.h"
#include "PolygonCursor.h"
class GE_API PolygonCreator //Created polygons' owner ship is moved to scene!!!
{
public:
    PolygonCreator(class Scene& scene);
    ~PolygonCreator()
    {
    
    }
    class Polygon* ApplyAndGetPolygon();

    void StartCreating(Vector2 position, int color = 1, int maxParticlesToDraw = 50);
    void SetPosition(Vector2 position);
    void SetEditingActive(bool isActive);
    // maxParticlesToDraw is the created polygon's outline glyph budget; raise
    // it for shapes whose perimeter is longer than the 50 cell default.
    Polygon* CreateSquarePolygon(Vector2 position, int size, float rotationAngle, int color = 1, int maxParticlesToDraw = 50);
    Polygon* CreateRectanglePolygon(Transform transform, int color = 1, int maxParticlesToDraw = 50);
    Polygon* CreateCircle(Vector2 position, float radius, int numSegments, int color = 1, int maxParticlesToDraw = 50);
    class Cursor* GetCursor() const { return m_Cursor; }
private:
    Polygon* m_CurrentPolygon;
    Scene& m_Scene;

    class Cursor* m_Cursor;
    
    bool m_IsCreating = false;
    bool m_IsEditingActive = false;

    
    void OnInput(int input);
};
