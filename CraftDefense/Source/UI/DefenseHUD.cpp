#include "DefenseHUD.h"
#include "Core/UIHandler.h"
#include "Systems/SunBank.h"
#include "Systems/SeedMenu.h"
#include "Systems/WaveDirector.h"
#include "CoreStructs/Vector.h"

DefenseHUD::DefenseHUD(UIHandler *uiHandler, SunBank &bank, SeedMenu &seedMenu, WaveDirector &waveDirector)
    : uiHandler(uiHandler), bank(bank), seedMenu(seedMenu), waveDirector(waveDirector)
{
    sunPanel = std::make_shared<UIPanel>();
    sunPanel->AddString(Vector2(0, 1), "SUN: " + std::to_string(bank.Get()));

    seedPanel = std::make_shared<UIPanel>();
    seedPanel->AddString(Vector2(0, 2), BuildSeedBarText());

    statusPanel = std::make_shared<UIPanel>();
    statusPanel->AddString(Vector2(0, 19), "");

    resultPanel = std::make_shared<UIPanel>();
    resultPanel->SetActive(false);
    resultPanel->AddString(Vector2(24, 10), "");

    if (uiHandler)
    {
        uiHandler->AddPanel(sunPanel);
        uiHandler->AddPanel(seedPanel);
        uiHandler->AddPanel(statusPanel);
        uiHandler->AddPanel(resultPanel);

        auto help = std::make_shared<UIData>();
        help->position = Vector2(0, 20);
        help->text = "WASD move  1-3 select  E plant  X shovel  F collect  ESC quit";
        uiHandler->AddString(help);
    }
}

void DefenseHUD::Update(float deltaTime)
{
    sunPanel->ChangeText(0, "SUN: " + std::to_string(bank.Get()));
    seedPanel->ChangeText(0, BuildSeedBarText());
    statusPanel->ChangeText(0, "Wave " + std::to_string(waveDirector.CurrentWaveNumber()) + "/" +
                                    std::to_string(waveDirector.TotalWaves()) + "   " + statusMessage);
}

void DefenseHUD::SetStatusMessage(const std::string &msg)
{
    statusMessage = msg;
}

void DefenseHUD::ShowResult(bool won)
{
    resultPanel->SetActive(true);
    resultPanel->ChangeText(0, won ? "YOU WIN! All waves cleared." : "GAME OVER - a zombie reached your base.");
}

std::string DefenseHUD::BuildSeedBarText() const
{
    std::string text;
    const auto &packets = seedMenu.Packets();

    for (size_t i = 0; i < packets.size(); i++)
    {
        const auto &p = packets[i];
        bool ready = p.ready >= p.recharge;
        bool afford = bank.Get() >= p.cost;
        std::string marker = (seedMenu.Selected() == static_cast<int>(i)) ? ">" : " ";
        std::string state = (ready && afford) ? "" : (!afford ? "$" : "~");
        text += marker + "[" + std::to_string(i + 1) + "]" + p.symbol + p.name + " " + std::to_string(p.cost) + state + "  ";
    }

    return text;
}
