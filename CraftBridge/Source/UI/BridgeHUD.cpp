#include "BridgeHUD.h"
#include "Core/UIHandler.h"
#include "CoreStructs/Vector.h"
#include <cstdio>

BridgeHUD::BridgeHUD(UIHandler *uiHandler) : uiHandler(uiHandler)
{
    // Rows 1-4, never row 0: row 0 means an explicit "\033[0;0H", which
    // (unlike an omitted parameter) terminals aren't guaranteed to treat as
    // row 1 - it's genuinely ambiguous, and every existing HUD in this repo
    // (e.g. CraftDefense/UI/DefenseHUD.cpp) already avoids it, starting at
    // row 1. Also never the bottom of the screen: Terrain draws each cliff
    // as a full outlined box reaching from groundY down to the screen
    // border, at both world x=0 and x=leftCliffX/rightCliffX, so any text
    // row below groundY collides with one of those vertical edges on every
    // level. Rows 1-4 sit above every level's groundY (>=15) and are only
    // ever shared with the build cursor at its very top boundary, a
    // harmless single-glyph overlap.
    infoPanel = std::make_shared<UIPanel>();
    infoPanel->AddString(Vector2(0, 1), "");

    controlsPanel = std::make_shared<UIPanel>();
    controlsPanel->AddString(Vector2(0, 2), "");

    statusPanel = std::make_shared<UIPanel>();
    statusPanel->AddString(Vector2(0, 3), "");

    resultPanel = std::make_shared<UIPanel>();
    resultPanel->SetActive(false);
    resultPanel->AddString(Vector2(24, 10), "");

    debugPanel = std::make_shared<UIPanel>();
    debugPanel->SetActive(DEBUG_COUNTS);
    debugPanel->AddString(Vector2(0, 4), "");

    if (uiHandler)
    {
        uiHandler->AddPanel(infoPanel);
        uiHandler->AddPanel(controlsPanel);
        uiHandler->AddPanel(statusPanel);
        uiHandler->AddPanel(resultPanel);
        uiHandler->AddPanel(debugPanel);
    }
}

void BridgeHUD::Update(const HudState &state)
{
    const char *phaseName = "BUILD";
    if (state.phase == BridgePhase::Test) phaseName = "TEST";
    else if (state.phase == BridgePhase::Won) phaseName = "WON";
    else if (state.phase == BridgePhase::Lost) phaseName = "LOST";

    char infoLine[160];
    if (state.phase == BridgePhase::Build)
    {
        std::snprintf(infoLine, sizeof(infoLine), "%s   %s   $%d / $%d   beams %d",
                      state.levelName.c_str(), phaseName,
                      static_cast<int>(state.spent), static_cast<int>(state.budget), state.beamCount);
    }
    else
    {
        std::snprintf(infoLine, sizeof(infoLine), "%s   %s   t %.1fs   beams %d   broken %d",
                      state.levelName.c_str(), phaseName, state.testTimer, state.beamCount, state.brokenCount);
    }
    infoPanel->ChangeText(0, infoLine);

    if (state.phase == BridgePhase::Build)
        controlsPanel->ChangeText(0, "WASD move  E connect  X delete  Q cancel  SPACE test  ESC quit");
    else if (state.phase == BridgePhase::Test)
        controlsPanel->ChangeText(0, "Watch it hold or fall...");
    else if (state.phase == BridgePhase::Won)
        controlsPanel->ChangeText(0, "N next level   R rebuild   ESC quit");
    else
        controlsPanel->ChangeText(0, "R retry   ESC quit");

    statusPanel->ChangeText(0, statusMessage);

    if (DEBUG_COUNTS && state.bodyCount >= 0)
    {
        char debugLine[64];
        std::snprintf(debugLine, sizeof(debugLine), "bodies %d  joints %d", state.bodyCount, state.jointCount);
        debugPanel->ChangeText(0, debugLine);
    }

    if (state.phase != lastShownPhase)
    {
        if (state.phase == BridgePhase::Won)
            ShowResult(true);
        else if (state.phase == BridgePhase::Lost)
            ShowResult(false);
        else
            HideResult();
        lastShownPhase = state.phase;
    }
}

void BridgeHUD::SetStatusMessage(const std::string &msg)
{
    statusMessage = msg;
}

void BridgeHUD::ShowResult(bool won)
{
    resultPanel->SetActive(true);
    resultPanel->ChangeText(0, won ? "BRIDGE HELD!" : "COLLAPSED");
}

void BridgeHUD::HideResult()
{
    resultPanel->SetActive(false);
}
