#pragma once
#include "Core/GameObject.h"

// The keyboard-driven build cursor (see CraftDefense/GridCursor.h for the
// pattern this follows). The engine has no mouse, so this is how the player
// points at a spot to place or delete a node/beam.
class BuildCursor : public GameObject
{
public:
    BuildCursor(class Scene &scene);

    void Init() override;
    void Move(float dx, float dy);
    void SetBounds(float minX, float maxX, float minY, float maxY);

    Vector2 Position() const { return transform.Position; }

private:
    float minX = 1.f, maxX = 78.f, minY = 1.f, maxY = 21.f;
};
