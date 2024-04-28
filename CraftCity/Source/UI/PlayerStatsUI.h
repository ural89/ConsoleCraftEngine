#pragma once
#include <memory>
#include "Core/UIHandler.h"
class PlayerStatsUI
{
public:
    PlayerStatsUI( UIHandler *uiHandler, class PlayerVault *playerVault, class CityStatics* cityStatics);
    void Update(float deltaTime);

private:
    UIHandler *uiHandler;
    PlayerVault *playerVault;
    CityStatics* cityStatics;
    
    std::shared_ptr<class UIPanel> playerStatsPanel;

};