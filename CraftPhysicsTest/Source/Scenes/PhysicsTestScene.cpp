#include "PhysicsTestScene.h"
#include "../RoadCreator/RoadCreator.h"
#include "Core/Input.h"
#include "Core/Component/RigidbodyComponent.h"
#include "Core/Physics/Polygon/PolygonCreator/PolygonCreator.h"
#include "Core/Physics/Polygon/JointCreator.h"
#include "Core/Physics/JointRenderer.h"
#include "Core/Physics/Polygon/Polygon.h"
#include "../Polygons/Car.h"
PhysicsTestScene::~PhysicsTestScene()
{
  delete polygonCreator;
  polygonCreator = nullptr;
  delete jointCreator;
  jointCreator = nullptr;
  delete jointRenderer;
  jointRenderer = nullptr;
}
void PhysicsTestScene::Init()
{
  Scene::Init();
  auto inputEvent = BIND_EVENT_FN(PhysicsTestScene::OnInput);
  Input::AddListener(inputEvent);
  polygonCreator = new PolygonCreator(*this);
  jointCreator = new JointCreator(*this);
  jointRenderer = new JointRenderer(*this);

  RoadCreator *roadCreator = new RoadCreator(*this, *polygonCreator);
  roadCreator->CreateRoad(6, {5, 15}, {54, 15});

  Car *car = new Car(*this, *polygonCreator);
  car->Init(Vector2(10, 9));
  // polygonCreator->CreateRectanglePolygon({Vector2(5, 9), Vector2(3, 9), 0});
  // polygonCreator->CreateSquarePolygon({40, 5}, 5, 0);
  // polygonCreator->CreateCircle({12, 5}, 3, 6);
  // polygonCreator->CreateCircle({25, 5}, 3, 6);
}

void PhysicsTestScene::Start()
{
  std::cout << " Press c to create vertex of a polygon \n";
  std::cout << " Press space to apply polygon \n";
}

void PhysicsTestScene::Update(float deltaTime)
{
  Scene::Update(deltaTime);
  jointRenderer->Update(deltaTime);
}

void PhysicsTestScene::OnInput(int input)
{
}
