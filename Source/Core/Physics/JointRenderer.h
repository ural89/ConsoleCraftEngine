#pragma once
class JointRenderer
{
public:
    JointRenderer(class Scene &scene);
    ~JointRenderer();
    void Update(float deltaTime);
private:
    Scene& scene;
    class LineDrawer* lineDrawer;
};