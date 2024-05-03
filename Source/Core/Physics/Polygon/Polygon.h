#pragma once
#include "../../../CoreStructs/Vector.h"
#include "../../../Core.h"
#include "../../../box2d/include/box2d/b2_body.h"   
#include "../../../box2d/include/box2d/b2_polygon_shape.h"
#include "../../UIHandler.h"
#include "../../LineDrawer.h"
#include "PolygonParticle.h"
#include "PolygonHelper.h"
#include <vector>
#include <memory>
class GE_API Polygon // This is not registered in scene. So use this with shared ptr to clear yourself.
{
    const int maxParticlesToDraw = 50;

public:
    Polygon(class Scene &scene, bool isClosed = false, int color = 1) : scene(scene), isClosed(isClosed), color(color)
    {
        lineDrawer = new LineDrawer(scene);
        CreateLineParticles(maxParticlesToDraw, color);
        debugUIPtr = std::make_shared<UIData>();
        debugUIPtr->position = Vector2(5, 29);
    }
    ~Polygon()
    {
        particles.clear();
        lineDrawer->ClearLines();
        delete lineDrawer;
        lineDrawer = nullptr;
   
    }

public:
    void AddParticle(Vector2 position, bool isFixed = false);
    void Init();
    void UpdateLines(float deltaTime);
    void OnCollided(Vector2 overlap, int particleIndex);
    void AddTorque(float torque);
    b2Body* GetBody() const
    {
        return polygonBody;
    }

    std::vector<PolygonParticle *> particles;
    std::vector<Vector2> edges;
  
    Vector2 GetCenter()
    {
        return GetCenterPointWorldPosition(particles);
    }
 
    bool isClosed = false;

private:
    Scene &scene;
    bool isReady = false;
    
    int color;

    b2PolygonShape polygonBox;
    b2Body* polygonBody;
    LineDrawer* lineDrawer;
    Vector2 lastDrawnLinePosition;
    std::shared_ptr<UIData> debugUIPtr;

private:
    void CreateLineParticles(int amount, int color);
    void DrawLine(Vector2 startPosition, Vector2 endPosition);

    void ClearParticles()
    {
        for (auto particle : particles)
        {
            particle->Destroy();
        }
        particles.clear();
    }

   
};