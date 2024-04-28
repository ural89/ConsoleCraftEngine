#include "PolygonCreator.h"
#include "../Polygon.h"
#include "../../../Scene.h"
#include "../../../Input.h"
PolygonCreator::PolygonCreator(Scene &scene) : scene(scene)
{
    auto inputEvent = BIND_EVENT_FN(PolygonCreator::OnInput);
    Input::AddListener(inputEvent);
    cursor = new Cursor(scene);
    scene.AddGameObject(cursor, Vector2(15, 15));
}

void PolygonCreator::StartCreating(Vector2 position)
{
    currentPolygon = new Polygon(scene, true, 400);
    currentPolygon->AddParticle(position);
    // std::cout << "Creating new poly" << '\n';
}

void PolygonCreator::SetPosition(Vector2 position)
{
    currentPolygon->AddParticle(position);
    currentPolygon->UpdateLines(0);
}

void PolygonCreator::CreateSquarePolygon(Vector2 position, int size, float rotationAngle)
{
    CreateRectanglePolygon({position, Vector2(size, size), rotationAngle});
}
void PolygonCreator::CreateRectanglePolygon(Transform transform)
{
    Polygon *polygon = new Polygon(scene);
    float rotationAngle = transform.Rotation * (3.14159f / 180.0f);

    float cosTheta = std::cos(rotationAngle);
    float sinTheta = std::sin(rotationAngle);

    Vector2 vertices[5] = {
        Vector2(transform.Position.X, transform.Position.Y),
        Vector2(transform.Position.X + transform.Size.X, transform.Position.Y),
        Vector2(transform.Position.X + transform.Size.X, transform.Position.Y + transform.Size.Y),
        Vector2(transform.Position.X, transform.Position.Y + transform.Size.Y),
        Vector2(transform.Position.X, transform.Position.Y + 1) // To make closed polygon
    };

    for (int i = 0; i < 5; ++i)
    {
        float rotatedX = cosTheta * (vertices[i].X - transform.Position.X) - sinTheta * (vertices[i].Y - transform.Position.Y) + transform.Position.X;
        float rotatedY = sinTheta * (vertices[i].X - transform.Position.X) + cosTheta * (vertices[i].Y - transform.Position.Y) + transform.Position.Y;

        polygon->AddParticle(Vector2(rotatedX, rotatedY));
    }

    scene.AddPolygon(polygon);
}
void PolygonCreator::CreateCircle(Vector2 position, float radius, int numSegments)
{
    Polygon *polygon = new Polygon(scene);
    float angleIncrement = (2 * M_PI) / numSegments;

    for (int i = 0; i < numSegments; ++i)
    {
        float angle = i * angleIncrement;
        float x = position.X + radius * std::cos(angle);
        float y = position.Y + radius * std::sin(angle);

        polygon->AddParticle(Vector2(x, y));
    }

    polygon->AddParticle(Vector2(position.X + radius, position.Y));

    scene.AddPolygon(polygon);
}
Polygon *PolygonCreator::ApplyAndGetPolygon()
{
    scene.AddPolygon(currentPolygon);
    return currentPolygon;
}

void PolygonCreator::OnInput(int input)
{
    if (input == 'c')
    {
        if (isCreating)
        {
            SetPosition(cursor->transform.Position);
        }
        else
        {
            isCreating = true;
            StartCreating(cursor->transform.Position);
        }
    }
    if (input == SPACEBAR)
    {
        if (currentPolygon)
        {
            if (currentPolygon->particles.size() > 2) // TODO: block linear polygons
            {
                isCreating = false;
                scene.AddPolygon(currentPolygon);
            }
            else
                std::cout << " Not enough particles created!" << '\n';
        }
    }
}
