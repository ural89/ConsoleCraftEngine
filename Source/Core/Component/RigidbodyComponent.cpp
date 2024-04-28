#include "RigidbodyComponent.h"
#include "../Scene.h"
void Rigidbody::Init()
{
  // owner->GetCurrentScene().collisionResolver->AddRigidbody(this);
  // Create dynamic body
  b2BodyDef bodyDef;
  bodyDef.fixedRotation = true; // freeze rotation
  bodyDef.type = b2_dynamicBody;
  bodyDef.position.Set(owner->transform.Position.X, owner->transform.Position.Y);

  body = owner->GetCurrentScene().World->CreateBody(&bodyDef);
  b2PolygonShape dynamicBox;
  dynamicBox.SetAsBox(owner->GetWidth() , owner->GetHeight());

  b2FixtureDef fixtureDef;
  fixtureDef.shape = &dynamicBox;
  fixtureDef.density = 1;
  fixtureDef.friction = 0.1f;
  fixtureDef.restitution = 0.8f;
  body->CreateFixture(&fixtureDef);

  debugUI.position = Vector2(0, 29);
  debugUIPtr = std::make_shared<UIData>(debugUI);
  owner->GetCurrentScene().uiHandler->AddString(debugUIPtr);
}
Rigidbody::~Rigidbody()
{
  owner->GetCurrentScene().collisionResolver->RemoveRigidbody(this);
}
void Rigidbody::Update(float deltaTime)
{
  elapsedSinceCollision += deltaTime;
  owner->transform.SetPosition(body->GetPosition().x, body->GetPosition().y);
  // body->ApplyForce(b2Vec2(500, 0), body->GetWorldCenter() , true);
  //  ProcessForce(deltaTime);
  // ProcessTorque(deltaTime);
}

void Rigidbody::ProcessForce(float deltaTime)
{
}
void Rigidbody::ProcessTorque(float deltaTime)
{
}
void Rigidbody::AddTorque(float torque)
{
}
void Rigidbody::OnCollided(Rigidbody &other)
{

  if (elapsedSinceCollision <= collisionFreq)
    return;
  elapsedSinceCollision = 0;
}

void Rigidbody::OnCollidedBorder(int border)
{
}

void Rigidbody::AddForce(Vector2 force)
{

  body->ApplyForce(b2Vec2(force.X, force.Y), body->GetWorldCenter(), true);
}

void Rigidbody::AddPulse(Vector2 pulse)
{
  body->ApplyLinearImpulse(b2Vec2(pulse.X, pulse.Y), body->GetWorldCenter(), true);
}
