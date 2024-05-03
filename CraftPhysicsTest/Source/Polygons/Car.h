#pragma once
class Car
{
public:
    Car(class Scene& scene, class PolygonCreator& polygonCreator);
    ~Car();
    void Init(class Vector2 position);
private:
    PolygonCreator& polygonCreator;
    Scene& scene;
};