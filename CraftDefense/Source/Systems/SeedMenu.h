#pragma once
#include "DefenseConfig.h"
#include <string>
#include <vector>

struct SeedPacket
{
    PlantType type;
    std::string name;
    std::string symbol;
    int cost;
    float recharge;
    float ready;
};

class SeedMenu
{
public:
    SeedMenu(class SunBank &bank);

    void Update(float deltaTime);
    int Selected() const { return selected; }
    const std::vector<SeedPacket> &Packets() const { return packets; }
    bool CanPlantSelected() const;
    void ConsumeSelected();

private:
    SunBank &bank;
    std::vector<SeedPacket> packets;
    int selected = -1;

    void OnInput(int input);
};
