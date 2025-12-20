#include "PolygonCreator.h"
#include "../Polygon.h"
#include "../../../Scene.h"
#include "../../../Input.h"
PolygonCreator::PolygonCreator(Scene &scene) : m_Scene(scene)
{
    auto inputEvent = BIND_EVENT_FN(PolygonCreator::OnInput);
    Input::AddListener(inputEvent);
    m_Cursor = new Cursor(scene);
    m_Scene.AddGameObject(m_Cursor, Vector2(15, 15));
    m_Cursor->isRenderable = false;
}

void PolygonCreator::StartCreating(Vector2 position, int color = 1)
{
    m_CurrentPolygon = new Polygon(m_Scene, true, color);
    m_CurrentPolygon->AddParticle(position);
    // std::cout << "Creating new poly" << '\n';
}
void PolygonCreator::SetEditingActive(bool isActive)
{
    m_Cursor->isRenderable = isActive;
    m_IsEditingActive = isActive;
}

void PolygonCreator::SetPosition(Vector2 position)
{
    m_CurrentPolygon->AddParticle(position);
    //m_CurrentPolygon->UpdateLines(0);
}

Polygon* PolygonCreator::CreateSquarePolygon(Vector2 position, int size, float rotationAngle, int color)
{
    return CreateRectanglePolygon({position, Vector2(size, size), rotationAngle}, color);
}
Polygon* PolygonCreator::CreateRectanglePolygon(Transform transform, int color)
{
    Polygon *polygon = new Polygon(m_Scene, true, color);
    float rotationAngle = transform.Rotation * (3.14159f / 180.0f);

    float cosTheta = std::cos(rotationAngle);
    float sinTheta = std::sin(rotationAngle);

    Vector2 vertices[4] = {
        Vector2(transform.Position.X, transform.Position.Y),
        Vector2(transform.Position.X + transform.Size.X, transform.Position.Y),
        Vector2(transform.Position.X + transform.Size.X, transform.Position.Y + transform.Size.Y),
        Vector2(transform.Position.X, transform.Position.Y + transform.Size.Y),
    };

    for (int i = 0; i < 4; ++i)
    {
        float rotatedX = cosTheta * (vertices[i].X - transform.Position.X) - sinTheta * (vertices[i].Y - transform.Position.Y) + transform.Position.X;
        float rotatedY = sinTheta * (vertices[i].X - transform.Position.X) + cosTheta * (vertices[i].Y - transform.Position.Y) + transform.Position.Y;

        polygon->AddParticle(Vector2(rotatedX, rotatedY));
    }

    m_Scene.AddPolygon(polygon);
    return polygon;
}
Polygon* PolygonCreator::CreateCircle(Vector2 position, float radius, int numSegments, int color)
{
    Polygon *polygon = new Polygon(m_Scene, true, color);
    float angleIncrement = (2 * M_PI) / numSegments;

    for (int i = 0; i < numSegments; ++i)
    {
        float angle = i * angleIncrement;
        float x = position.X + radius * std::cos(angle);
        float y = position.Y + radius * std::sin(angle);

        polygon->AddParticle(Vector2(x, y));
    }

    polygon->AddParticle(Vector2(position.X + radius, position.Y));

    m_Scene.AddPolygon(polygon);
    return polygon;
}
Polygon *PolygonCreator::ApplyAndGetPolygon()
{
    m_Scene.AddPolygon(m_CurrentPolygon);
    return m_CurrentPolygon;
}

void PolygonCreator::OnInput(int input)
{
    if (!m_IsEditingActive)
    {
        return;
    }
    if (input == 'e')
    {
        if (m_IsCreating)
        {
            SetPosition(m_Cursor->transform.Position);
        }
        else
        {
            m_IsCreating = true;
            StartCreating(m_Cursor->transform.Position);
        }
    }
    if (input == SPACEBAR)
    {
        if (m_CurrentPolygon)
        {
            if (m_CurrentPolygon->particles.size() > 2) // TODO: block linear polygons
            {
                m_IsCreating = false;
                m_Scene.AddPolygon(m_CurrentPolygon);
            }
            else
                std::cout << " Not enough particles created!" << '\n';
        }
    }
}
