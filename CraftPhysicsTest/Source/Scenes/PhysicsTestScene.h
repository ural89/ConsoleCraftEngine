#pragma once
#include "Core/Scene.h"

#include <memory>
class PhysicsTestScene : public Scene
{
public:
    ~PhysicsTestScene();

    void Init() override;
    void Start() override;
    void Update(float deltaTime) override;

private:
    class PolygonCreator *polygonCreator;
    class JointCreator *jointCreator;
    class JointRenderer *jointRenderer;
    void OnInput(int input);
    

};
