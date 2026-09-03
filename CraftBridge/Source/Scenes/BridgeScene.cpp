#include "BridgeScene.h"
#include "../Levels/Levels.h"
#include "../Systems/BuildCursor.h"
#include "../Systems/Terrain.h"
#include "../Systems/Deck.h"
#include "../Systems/BridgeGraph.h"
#include "../GameObjects/Vehicle.h"
#include "Core/Input.h"
#include "Core/Physics/JointRenderer.h"
#include "Core/Physics/Polygon/JointCreator.h"
#include "Core/Physics/Polygon/PolygonCreator/PolygonCreator.h"
#include <cctype>

BridgeScene::~BridgeScene()
{
    // Reverse creation order: every system's destructor tears its shapes down
    // through the scene, so the creators it borrows must outlive it.
    delete vehicle;
    delete graph;
    delete deck;
    delete terrain;
    delete jointRenderer;
    delete jointCreator;
    delete polygonCreator;
}

void BridgeScene::Init()
{
    Scene::Init();

    polygonCreator = new PolygonCreator(*this);
    jointCreator = new JointCreator(*this);
    jointRenderer = new JointRenderer(*this);

    // Both creators own a WASD-driven Cursor of their own. PolygonCreator
    // starts with editing off, but JointCreator does not, and its free-form
    // 'j' distance-joint tool plus its visible cursor would sit on top of the
    // build cursor and hand out free, uncosted ties.
    jointCreator->SetEditingActive(false);

    terrain = new Terrain(*this, *polygonCreator);
    deck = new Deck(*this, *polygonCreator, *jointCreator);
    graph = new BridgeGraph(*this, *polygonCreator, *jointCreator);
    vehicle = new Vehicle(*this, *polygonCreator, *jointCreator);

    cursor = new BuildCursor(*this);
    AddGameObject(cursor, Vector2(20.f, 12.f));

    auto inputEvent = BIND_EVENT_FN(BridgeScene::OnInput);
    Input::AddListener(inputEvent);

    LoadLevel(0);
}

void BridgeScene::Start()
{
    std::cout << " WASD moves the cursor, E connects two points, SPACE tests the bridge \n";
}

void BridgeScene::TeardownPhysics()
{
    // Order matters: a beam can be pinned to a plank and a plank to a cliff,
    // and destroying a body takes every joint on it with it.
    vehicle->Despawn();
    graph->Teardown();
    deck->Teardown();
    terrain->Teardown();
}

void BridgeScene::LoadLevel(int index)
{
    const auto &levels = Levels::All();
    if (index < 0 || index >= static_cast<int>(levels.size()))
        return;

    levelIndex = index;
    currentLevel = levels[index];

    TeardownPhysics();

    terrain->Build(currentLevel);
    deck->Build(currentLevel, *terrain);
    deck->SetFrozen(true); // the deck must hold its nominal shape while you build against it
    graph->Reset(currentLevel.budget);

    phase = BridgePhase::Build;
    testTimer = 0.f;
    accumulator = 0.f;

    cursor->SetRenderable(true);
    // minY = 6: rows 1-4 are the HUD (see BridgeHUD.cpp) and every level's
    // groundY is >= 15, so this still covers the full build area.
    cursor->SetBounds(1.f, static_cast<float>(SCREENWIDTH) - 1.f, 6.f, static_cast<float>(SCREENHEIGHT) - 2.f);
    cursor->transform.SetPosition((currentLevel.leftCliffX + currentLevel.rightCliffX) * 0.5f, currentLevel.groundY - 3.f);

    hud.SetStatusMessage(currentLevel.name + " - build a bridge!");
}

void BridgeScene::RetryLevel()
{
    TeardownPhysics();

    terrain->Build(currentLevel);
    deck->Build(currentLevel, *terrain);
    deck->SetFrozen(true);

    graph->SetFrozen(true);
    graph->Instantiate(*terrain, *deck);

    phase = BridgePhase::Build;
    testTimer = 0.f;
    accumulator = 0.f;
    cursor->SetRenderable(true);

    hud.SetStatusMessage("Rebuilt - try again");
}

void BridgeScene::NextLevel()
{
    int next = levelIndex + 1;
    if (next >= static_cast<int>(Levels::All().size()))
    {
        hud.SetStatusMessage("All levels complete!");
        return;
    }
    LoadLevel(next);
}

void BridgeScene::StartTest()
{
    if (graph->BeamCount() == 0)
    {
        hud.SetStatusMessage("Build something first!");
        return;
    }

    graph->ClearPending();
    graph->SetFrozen(false);
    deck->SetFrozen(false);
    vehicle->Spawn(currentLevel.startX, currentLevel.groundY);

    phase = BridgePhase::Test;
    testTimer = 0.f;
    cursor->SetRenderable(false);
    hud.SetStatusMessage("Testing...");
}

void BridgeScene::TryConnect()
{
    if (!graph->HasPending())
    {
        int idx = graph->FindOrCreateNode(cursor->Position(), *terrain, *deck);
        graph->SetPending(idx);
        hud.SetStatusMessage("Pick the second point (Q to cancel)");
        return;
    }

    int a = graph->PendingNode();
    int b = graph->FindOrCreateNode(cursor->Position(), *terrain, *deck);
    graph->ClearPending();

    if (a == b)
    {
        hud.SetStatusMessage("Cancelled");
        return;
    }

    std::string message;
    graph->AddBeam(a, b, message);
    hud.SetStatusMessage(message);
}

void BridgeScene::CancelPending()
{
    if (graph->HasPending())
    {
        graph->ClearPending();
        hud.SetStatusMessage("Cancelled");
    }
}

void BridgeScene::TryDelete()
{
    std::string message;
    graph->RemoveNearestBeam(cursor->Position(), message);
    hud.SetStatusMessage(message);
}

void BridgeScene::OnInput(int input)
{
    int c = std::tolower(input);

    if (phase == BridgePhase::Build)
    {
        if (c == 'w') cursor->Move(0.f, -CURSOR_STEP_Y);
        else if (c == 's') cursor->Move(0.f, CURSOR_STEP_Y);
        else if (c == 'a') cursor->Move(-CURSOR_STEP_X, 0.f);
        else if (c == 'd') cursor->Move(CURSOR_STEP_X, 0.f);
        else if (c == 'e') TryConnect();
        else if (c == 'q') CancelPending();
        else if (c == 'x') TryDelete();
        else if (input == SPACEBAR) StartTest();
    }
    else if (phase == BridgePhase::Won)
    {
        if (c == 'n') NextLevel();
        else if (c == 'r') RetryLevel();
    }
    else if (phase == BridgePhase::Lost)
    {
        if (c == 'r') RetryLevel();
    }
    // Test phase: no player input, just watch it run.
}

void BridgeScene::EvaluateTest()
{
    if (!vehicle->IsSpawned())
        return;

    Vector2 pos = vehicle->ChassisPosition();
    float failY = currentLevel.groundY + FAIL_Y_MARGIN;

    if (pos.X >= currentLevel.finishX && pos.Y < failY)
    {
        phase = BridgePhase::Won;
        hud.SetStatusMessage("Bridge held!");
        return;
    }

    if (pos.Y > failY)
    {
        phase = BridgePhase::Lost;
        hud.SetStatusMessage("The car fell!");
        return;
    }

    if (testTimer > TEST_TIMEOUT)
    {
        phase = BridgePhase::Lost;
        hud.SetStatusMessage("Ran out of time");
        return;
    }
}

void BridgeScene::RefreshHud()
{
    HudState state;
    state.levelName = currentLevel.name;
    state.phase = phase;
    state.budget = currentLevel.budget;
    state.spent = graph->Spent();
    state.beamCount = graph->BeamCount();
    state.brokenCount = graph->BrokenCount();
    state.testTimer = testTimer;

    if (DEBUG_COUNTS)
    {
        state.bodyCount = world->GetBodyCount();
        state.jointCount = world->GetJointCount();
    }

    hud.Update(state);
}

void BridgeScene::Update(float deltaTime)
{
    accumulator += (deltaTime < MAX_FRAME_TIME) ? deltaTime : MAX_FRAME_TIME;

    int steps = 0;
    while (accumulator >= FIXED_DT && steps < MAX_STEPS_PER_FRAME)
    {
        Scene::Update(FIXED_DT); // steps Box2D and redraws every polygon's outline

        if (phase == BridgePhase::Test)
        {
            graph->UpdateStress();
            testTimer += FIXED_DT;
        }

        accumulator -= FIXED_DT;
        steps++;
    }

    if (steps == 0)
        return;

    if (phase == BridgePhase::Test)
        EvaluateTest();

    jointRenderer->Update(FIXED_DT);
    graph->RefreshVisuals(cursor->Position(), phase == BridgePhase::Build);
    RefreshHud();
}
