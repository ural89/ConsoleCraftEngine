#include "PolygonParticle.h"

void PolygonParticle::Init()
{
}

void PolygonParticle::OnReady()
{
    Rigidbody *rb = new Rigidbody(*this);
    AddComponent(rb);
}
