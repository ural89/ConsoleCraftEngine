#include "PolygonFactory.h"
#include "Core/Physics/Polygon/Polygon.h"
#include "Core/Physics/Polygon/PolygonCreator/PolygonCreator.h"
#include "Core/Scene.h"
#include <cmath>

namespace PolygonFactory
{
    Polygon *CreateBox(PolygonCreator &creator, Vector2 center, Vector2 size, float rotationDegrees, int color, int maxParticlesToDraw)
    {
        // CreateRectanglePolygon lays the box out from `Position` to
        // `Position + Size` and rotates every vertex about `Position`, so the
        // box centre lands on Position + R * (Size / 2). Invert that.
        float radians = rotationDegrees * (3.14159265f / 180.0f);
        float cosTheta = std::cos(radians);
        float sinTheta = std::sin(radians);
        Vector2 half = size * 0.5f;
        Vector2 centreOffset(cosTheta * half.X - sinTheta * half.Y,
                             sinTheta * half.X + cosTheta * half.Y);

        return creator.CreateRectanglePolygon({center - centreOffset, size, rotationDegrees}, color, maxParticlesToDraw);
    }

    void SetPhysics(Polygon *polygon, float density, float friction, short groupIndex,
                    unsigned short categoryBits, unsigned short maskBits)
    {
        if (!polygon || !polygon->GetBody())
            return;

        b2Fixture *fixture = polygon->GetBody()->GetFixtureList();
        if (!fixture)
            return;

        fixture->SetDensity(density);
        fixture->SetFriction(friction);
        fixture->SetRestitution(0.f);

        b2Filter filter;
        filter.groupIndex = groupIndex;
        filter.categoryBits = categoryBits;
        filter.maskBits = maskBits;
        fixture->SetFilterData(filter);

        polygon->GetBody()->ResetMassData();
    }

    void SetStatic(Polygon *polygon, bool isStatic)
    {
        if (!polygon || !polygon->GetBody())
            return;

        polygon->GetBody()->SetType(isStatic ? b2_staticBody : b2_dynamicBody);
        polygon->GetBody()->SetAwake(true);
    }

    void PrepareCorners(Polygon *polygon, bool visible)
    {
        if (!polygon)
            return;

        // A shape can end up with fewer hull vertices than the polygon was
        // given - PolygonCreator::CreateCircle repeats the first point to close
        // the ring and b2PolygonShape::Set drops it - and Polygon::UpdateLines
        // only ever moves the ones the hull kept. Left visible, the leftovers
        // sit at their creation position for the rest of the level.
        size_t hullCount = polygon->particles.size();
        if (polygon->GetBody() && polygon->GetBody()->GetFixtureList())
        {
            auto *shape = dynamic_cast<b2PolygonShape *>(polygon->GetBody()->GetFixtureList()->GetShape());
            if (shape)
                hullCount = static_cast<size_t>(shape->m_count);
        }

        for (size_t i = 0; i < polygon->particles.size(); i++)
        {
            auto *particle = polygon->particles[i];
            particle->isRenderable = visible && i < hullCount;
            particle->hasCollider = false;
            particle->canFindable = false;
            particle->isNavIgnore = true;
        }
    }

    void Destroy(Scene &scene, Polygon *&polygon)
    {
        if (!polygon)
            return;

        scene.RemovePolygon(polygon);
        polygon = nullptr;
    }
}
