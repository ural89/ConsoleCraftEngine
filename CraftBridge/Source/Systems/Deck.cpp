#include "Deck.h"
#include "Terrain.h"
#include "PolygonFactory.h"
#include "../BridgeConfig.h"
#include "Core/Physics/Polygon/Polygon.h"
#include "Core/Physics/Polygon/PolygonCreator/PolygonCreator.h"
#include "Core/Physics/Polygon/JointCreator.h"
#include "Core/Scene.h"

Deck::Deck(Scene &scene, PolygonCreator &polygonCreator, JointCreator &jointCreator)
    : scene(scene), polygonCreator(polygonCreator), jointCreator(jointCreator)
{
}

Deck::~Deck()
{
    Teardown();
}

void Deck::Build(const LevelData &level, Terrain &terrain)
{
    Teardown();

    float gapWidth = level.rightCliffX - level.leftCliffX;
    float segmentWidth = gapWidth / static_cast<float>(level.deckSegments);
    float halfW = segmentWidth * 0.5f;

    Polygon *previous = nullptr;

    for (int i = 0; i < level.deckSegments; i++)
    {
        float centerX = level.leftCliffX + segmentWidth * (static_cast<float>(i) + 0.5f);

        Polygon *plank = PolygonFactory::CreateBox(polygonCreator, Vector2(centerX, level.groundY),
                                                   Vector2(segmentWidth, DECK_THICKNESS), 0.f,
                                                   DECK_COLOR, DECK_GLYPHS);
        PolygonFactory::SetPhysics(plank, DECK_DENSITY, 0.9f, DECK_GROUP, CATEGORY_DECK, MASK_ALL);
        PolygonFactory::PrepareCorners(plank, false);
        segments.push_back(plank);

        b2Body *pinTo = (i == 0) ? terrain.LeftBody() : previous->GetBody();
        jointCreator.CreateRevoluteJoint(pinTo, plank->GetBody(), Vector2(centerX - halfW, level.groundY));

        previous = plank;
    }

    if (previous)
    {
        float rightEdgeX = level.leftCliffX + segmentWidth * static_cast<float>(level.deckSegments);
        jointCreator.CreateRevoluteJoint(previous->GetBody(), terrain.RightBody(), Vector2(rightEdgeX, level.groundY));
    }
}

void Deck::Teardown()
{
    // No joint pointers are kept: destroying a plank body takes its hinges
    // with it, whichever end of the chain they were on.
    for (Polygon *plank : segments)
        PolygonFactory::Destroy(scene, plank);
    segments.clear();
}

void Deck::SetFrozen(bool frozen)
{
    for (Polygon *plank : segments)
        PolygonFactory::SetStatic(plank, frozen);
}

b2Body *Deck::SegmentBody(int index) const
{
    return segments[index]->GetBody();
}

Vector2 Deck::SegmentPosition(int index) const
{
    b2Vec2 p = segments[index]->GetBody()->GetPosition();
    return Vector2(p.x, p.y);
}
