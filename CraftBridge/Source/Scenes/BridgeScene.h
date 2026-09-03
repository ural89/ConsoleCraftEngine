#pragma once
#include "Core/Scene.h"
#include "../BridgeConfig.h"
#include "../Levels/LevelData.h"
#include "../UI/BridgeHUD.h"

// Owns the whole game: level state, the fixed-timestep accumulator (see
// CraftBridge.md "Fixed timestep"), and the Build/Test/Won/Lost phase machine.
//
// Set up like CraftPhysicsTest's PhysicsTestScene: a PolygonCreator makes every
// shape, a JointCreator makes every joint, a JointRenderer draws them, and the
// scene itself draws the polygons - so nothing here has a Draw() of its own.
class BridgeScene : public Scene
{
public:
    ~BridgeScene();

    void Init() override;
    void Start() override;
    void Update(float deltaTime) override;

private:
    void OnInput(int input);

    void LoadLevel(int index);
    void RetryLevel();
    void NextLevel();
    void StartTest();

    void TeardownPhysics();
    void EvaluateTest();
    void RefreshHud();

    void TryConnect();
    void CancelPending();
    void TryDelete();

    class PolygonCreator *polygonCreator = nullptr;
    class JointCreator *jointCreator = nullptr;
    class JointRenderer *jointRenderer = nullptr;

    class Terrain *terrain = nullptr;
    class Deck *deck = nullptr;
    class BridgeGraph *graph = nullptr;
    class Vehicle *vehicle = nullptr;

    class BuildCursor *cursor = nullptr; // GameObject; owned/deleted by Scene
    BridgeHUD hud{uiHandler};

    LevelData currentLevel;
    int levelIndex = 0;
    BridgePhase phase = BridgePhase::Build;

    float accumulator = 0.f;
    float testTimer = 0.f;
};
