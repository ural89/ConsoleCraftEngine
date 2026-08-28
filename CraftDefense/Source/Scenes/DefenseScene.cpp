#include "DefenseScene.h"
#include "DefenseConfig.h"
#include "Grid/LaneGrid.h"
#include "Systems/SunBank.h"
#include "Systems/SunManager.h"
#include "Systems/SeedMenu.h"
#include "Systems/WaveDirector.h"
#include "Systems/PlantFactory.h"
#include "UI/DefenseHUD.h"
#include "GameObjects/GridCursor.h"
#include "GameObjects/Plants/Plant.h"
#include "Core/Input.h"
#include <cstdlib>
#include <ctime>

DefenseScene::~DefenseScene()
{
    delete hud;
    delete waveDirector;
    delete seedMenu;
    delete sunManager;
    delete bank;
    delete grid;
}

void DefenseScene::Init()
{
    srand(static_cast<unsigned int>(time(nullptr)));

    grid = new LaneGrid();
    bank = new SunBank();
    sunManager = new SunManager(*this, *bank);
    seedMenu = new SeedMenu(*bank);
    waveDirector = new WaveDirector(*this, *grid, *this);
    hud = new DefenseHUD(uiHandler, *bank, *seedMenu, *waveDirector);

    cursor = new GridCursor(*this);
    AddGameObject(cursor, CellToWorld(0, 0));

    auto inputEvent = BIND_EVENT_FN(DefenseScene::OnInput);
    Input::AddListener(inputEvent);
}

void DefenseScene::Update(float deltaTime)
{
    Scene::Update(deltaTime);

    if (!gameEnded)
    {
        sunManager->Update(deltaTime);
        seedMenu->Update(deltaTime);
        waveDirector->Update(deltaTime);

        if (waveDirector->IsComplete())
            EndGame(true);

        cursor->Recolor(ComputeCanPlant(), sunManager->HasLiveTokenAt(cursor->Col(), cursor->Row()));
    }
    else
    {
        endScreenTimer += deltaTime;
        if (endScreenTimer >= 2.5f)
            hasGameOver = true;
    }

    hud->Update(deltaTime);
}

bool DefenseScene::ComputeCanPlant() const
{
    return seedMenu->CanPlantSelected() && grid->IsFree(cursor->Col(), cursor->Row());
}

void DefenseScene::OnInput(int input)
{
    if (gameEnded)
        return;

    int col = cursor->Col();
    int row = cursor->Row();
    int c = std::tolower(input);

    if (c == 'w')
        cursor->MoveTo(col, row - 1);
    else if (c == 's')
        cursor->MoveTo(col, row + 1);
    else if (c == 'a')
        cursor->MoveTo(col - 1, row);
    else if (c == 'd')
        cursor->MoveTo(col + 1, row);
    else if (c == 'e')
        TryPlant();
    else if (c == 'x')
        TryShovel();
    else if (c == 'f')
        TryCollectSun();
}

void DefenseScene::TryPlant()
{
    int col = cursor->Col();
    int row = cursor->Row();

    if (!grid->IsFree(col, row))
    {
        hud->SetStatusMessage("Cell occupied");
        return;
    }
    if (!seedMenu->CanPlantSelected())
    {
        hud->SetStatusMessage("Can't plant that here");
        return;
    }

    const SeedPacket &packet = seedMenu->Packets()[seedMenu->Selected()];
    Plant *plant = PlantFactory::Create(packet.type, *this, *grid, *sunManager);
    AddGameObject(plant, CellToWorld(col, row));
    grid->Place(plant, col, row);
    bank->Spend(packet.cost);
    seedMenu->ConsumeSelected();
    hud->SetStatusMessage("Planted " + packet.name);
}

void DefenseScene::TryShovel()
{
    int col = cursor->Col();
    int row = cursor->Row();

    Plant *p = grid->At(col, row);
    if (!p)
    {
        hud->SetStatusMessage("Nothing to remove");
        return;
    }

    grid->Clear(col, row);
    p->Destroy();
    hud->SetStatusMessage("Removed plant");
}

void DefenseScene::TryCollectSun()
{
    if (sunManager->CollectAt(cursor->Col(), cursor->Row()))
        hud->SetStatusMessage("+25 sun");
    else
        hud->SetStatusMessage("No sun here");
}

void DefenseScene::OnLaneBreached(int lane)
{
    if (!gameEnded)
        EndGame(false);
}

void DefenseScene::EndGame(bool won)
{
    gameEnded = true;
    endScreenTimer = 0.f;
    hud->ShowResult(won);
    hud->SetStatusMessage(won ? "Victory!" : "Defeat!");
}
