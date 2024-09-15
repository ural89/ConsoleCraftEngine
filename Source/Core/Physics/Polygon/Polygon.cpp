#include "Polygon.h"
#include "../../../Core/Scene.h"
void Polygon::AddParticle(Vector2 position, bool isFixed)
{
    auto polygonParticle = new PolygonParticle(scene);
    polygonParticle->isFixed = isFixed;
    particles.push_back(polygonParticle);
    polygonParticle->overrideColor = color;
    scene.AddGameObject(polygonParticle, position);
}

void Polygon::Init()
{
    size_t numParticles = particles.size();

    b2Vec2 vertices[numParticles];
    Vector2 centroid = GetCenterPointWorldPosition(particles);
    for (size_t i = 0; i < numParticles; ++i)
    {
        vertices[i].Set(particles[i]->transform.Position.X - centroid.X, particles[i]->transform.Position.Y - centroid.Y);
    }
    // centroid = centroid / static_cast<float>(numParticles);
    b2Vec2 initialPosition(centroid.X, centroid.Y);
    // Create dynamic body
    b2BodyDef polygonBodyDef;
    polygonBodyDef.type = b2_dynamicBody;
    polygonBodyDef.allowSleep = false;
    polygonBodyDef.position = initialPosition;
    polygonBody = scene.world->CreateBody(&polygonBodyDef);
    polygonBox.Set(vertices, numParticles);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &polygonBox;
    fixtureDef.density = 1;
    fixtureDef.friction = 0.9f;
    fixtureDef.restitution = 0.2f;
    polygonBody->CreateFixture(&fixtureDef);
    isReady = true;
}

void Polygon::UpdateLines(float deltaTime)
{
    lineDrawer->ResetDrawingParticleIndex();
    int numberOfLineToCreate = 0;
    if (polygonBody)
    {

        b2Fixture *fixture = polygonBody->GetFixtureList();
        if (fixture)
        {
            if (b2PolygonShape *shape = dynamic_cast<b2PolygonShape *>(fixture->GetShape()))
            {
                for (size_t i = 0; i < shape->m_count; i++)
                {
                    b2Vec2 vertexPos = polygonBody->GetWorldPoint(shape->m_vertices[i]);
                    b2Vec2 vertexPos2 = polygonBody->GetWorldPoint(shape->m_vertices[(i + 1) % shape->m_count]);
                    // particles[i+1]->transform.SetPosition(vertexPos.x, vertexPos.y);
                    particles[i]->transform.SetPosition(vertexPos.x, vertexPos.y); // Update position of corners
                    DrawLine(Vector2(vertexPos.x, vertexPos.y), Vector2(vertexPos2.x, vertexPos2.y));
                }
            }
        }
    }
}

void Polygon::OnCollided(Vector2 overlap, int particleIndex)
{
}

void Polygon::CreateLineParticles(int amount, int color)
{
    lineDrawer->CreateLineParticles(amount, color);
}

void Polygon::DrawLine(Vector2 startPosition, Vector2 endPosition)
{
    lineDrawer->DrawLine(startPosition, endPosition);
}

void Polygon::AddTorque(float torque)
{
}
