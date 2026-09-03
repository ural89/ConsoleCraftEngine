#pragma once
#include "../BridgeConfig.h"
#include <memory>
#include <string>

struct HudState
{
    std::string levelName;
    BridgePhase phase = BridgePhase::Build;
    float budget = 0.f;
    float spent = 0.f;
    int beamCount = 0;
    int brokenCount = 0;
    float testTimer = 0.f;
    int bodyCount = -1;
    int jointCount = -1;
};

// Modelled on CraftDefense/UI/DefenseHUD.{h,cpp}: one UIPanel per row, added
// once in the constructor and refreshed via ChangeText every frame (which
// only actually redraws when the text changed).
class BridgeHUD
{
public:
    BridgeHUD(class UIHandler *uiHandler);

    void Update(const HudState &state);
    void SetStatusMessage(const std::string &msg);
    void ShowResult(bool won);
    void HideResult();

private:
    UIHandler *uiHandler;

    std::shared_ptr<struct UIPanel> infoPanel;
    std::shared_ptr<struct UIPanel> controlsPanel;
    std::shared_ptr<struct UIPanel> statusPanel;
    std::shared_ptr<struct UIPanel> resultPanel;
    std::shared_ptr<struct UIPanel> debugPanel;

    std::string statusMessage;
    BridgePhase lastShownPhase = BridgePhase::Build; // edge-triggers ShowResult/HideResult
};
