#pragma once
#include "Core/GameObject.h"
class SelectCursor : public GameObject {
public:
  SelectCursor(class Scene &scene) : GameObject("SelectCursor", scene) {}
  ~SelectCursor() {}
  void Init() override {
    sprite = {
        {1, 1},
        {1, 1},
    };
  }
  void SetSize(Vector2 size, char &&symbol);
  int GetWidth() const override { return size.X; }
  int GetHeight() const override { return size.Y; }

  GameObject *GetCollidedObject() { return collidedObject; }
  void ResetCollidedObject() { collidedObject = nullptr; }
  void OnCollided(GameObject &other) override;
  void OnCollisionExit(GameObject &other) override;
  bool CanBuild = true;

private:
  GameObject *collidedObject = nullptr;
  Vector2 size;
  void Update(float deltaTime) override;
  float initTime = 1;
};
