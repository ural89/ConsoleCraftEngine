#include "PlayerStatsUI.h"

#include "CoreStructs/Vector.h"
#include "../CityStatics/PlayerVault.h"
#include "../CityStatics/CityStatics.h"
PlayerStatsUI::PlayerStatsUI(UIHandler *uiHandler, PlayerVault *playerVault, CityStatics* cityStatics)  : uiHandler(uiHandler), playerVault(playerVault), cityStatics(cityStatics)
{
    playerStatsPanel = std::make_shared<UIPanel>();
    playerStatsPanel->AddString(Vector2(SCREENWIDTH - 3, SCREENHEIGHT - 3), "$100");
    playerStatsPanel->AddString(Vector2(SCREENWIDTH - 6, SCREENHEIGHT - 2), "People: ");
    uiHandler->AddPanel(playerStatsPanel);
}


void PlayerStatsUI::Update(float deltaTime)
{
    playerStatsPanel->ChangeText(0, "$" + std::to_string((playerVault->GetMoneyAmount())));
    playerStatsPanel->ChangeText(1, "People: " + std::to_string((cityStatics->TotalPeople)));
}
