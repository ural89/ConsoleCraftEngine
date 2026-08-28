#pragma once
#include <memory>
#include <string>

class DefenseHUD
{
public:
    DefenseHUD(class UIHandler *uiHandler, class SunBank &bank, class SeedMenu &seedMenu, class WaveDirector &waveDirector);

    void Update(float deltaTime);
    void SetStatusMessage(const std::string &msg);
    void ShowResult(bool won);

private:
    UIHandler *uiHandler;
    SunBank &bank;
    SeedMenu &seedMenu;
    WaveDirector &waveDirector;

    std::shared_ptr<struct UIPanel> sunPanel;
    std::shared_ptr<struct UIPanel> seedPanel;
    std::shared_ptr<struct UIPanel> statusPanel;
    std::shared_ptr<struct UIPanel> resultPanel;
    std::string statusMessage;

    std::string BuildSeedBarText() const;
};
