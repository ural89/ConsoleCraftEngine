#pragma once
#include "Component.h"
#include "../GameObject.h"
#include "../../CoreStructs/Vector.h"
#include "../UIHandler.h"
#include "../../Core.h"
class b2Body;
class GE_API Rigidbody : public Component
{

public:
  Rigidbody(GameObject &gameObject) : Component(gameObject)
  {
  }
  ~Rigidbody();
  void Init() override;
  void Update(float deltaTime) override;
  void AddTorque(float torque);
  void OnCollided(Rigidbody &other);
  void OnCollidedBorder(int border);
  void AddForce(Vector2 force);
  void AddPulse(Vector2 pulse);

  Transform &GetTransform()
  {

    return owner->transform;
  };
  float GetMass() const
  {
    return mass;
  }
  int GetWidth() const
  {
    return owner->GetWidth();
  }
  int GetHeight() const
  {
    return owner->GetHeight();
  }
  Vector2 GetCenterPosition()
  {
    return Vector2(owner->transform.Position.X + GetWidth() / 2, owner->transform.Position.Y + GetHeight() / 2);
  }
  b2Body *GetBody() const
  {
    return body;
  }
  Vector2 gravity = Vector2(0, 0);
  Vector2 velocity = Vector2(0.00001f, 0); // To prevent clear flag issues

  bool isKinematic = false;
  bool canCollide = true;
  bool canCollideBorder = true;
  bool isDebug = false;
  float drag = 0.9;

private:
  std::shared_ptr<UIData> debugUIPtr;
  UIData debugUI;

  float mass = 1;

  float momentOfInertia = 0;
  float angularVelocity = 0;
  float angularDrag = 0.3;
  b2Body *body;
  Vector2 force;
  Vector2 pulse;

  float elapsedSinceCollision = 0;
  float collisionFreq = 0.1f;

  void ProcessForce(float deltaTime);
  void ProcessTorque(float deltaTime);
};
