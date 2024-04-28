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
    Polygon(class Scene &scene, bool isClosed = false, float stiffness = 400) : scene(scene), isClosed(isClosed), stiffness(stiffness)
    {
        lineDrawer = new LineDrawer(scene);
        CreateLineParticles(maxParticlesToDraw);
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
    void AddParticle(Vector2 position, bool isFixed = false);

    void Init();
    void UpdateLines(float deltaTime);
    void OnCollided(Vector2 overlap, int particleIndex);
    void AddTorque(float torque);
    std::vector<PolygonParticle *> particles;

    std::vector<Vector2> edges;
  
    Vector2 GetCenter()
    {
        return GetCenterPointWorldPosition(particles);
    }
    void SetStiffness(float stiffness)
    {
        this->stiffness = stiffness;
    }
    bool isClosed = false;

private:
    Scene &scene;
    bool isReady = false;
    

    float stiffness = 400;
    
    b2PolygonShape polygonBox;
    b2Body* polygonBody;
    LineDrawer* lineDrawer;
    Vector2 lastDrawnLinePosition;
    std::shared_ptr<UIData> debugUIPtr;

private:
    void CreateLineParticles(int amount);
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