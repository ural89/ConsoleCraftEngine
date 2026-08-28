#include "SeedMenu.h"
#include "SunBank.h"
#include "Core/Input.h"

SeedMenu::SeedMenu(SunBank &bank) : bank(bank)
{
    packets = {
        {PlantType::Sunflower, "Sunflower", "*", 50, 7.5f, 7.5f},
        {PlantType::Peashooter, "Peashooter", "o", 100, 7.5f, 7.5f},
        {PlantType::Wallnut, "Wall-nut", "#", 50, 20.f, 20.f},
    };

    auto keyEvent = BIND_EVENT_FN(SeedMenu::OnInput);
    Input::AddListener(keyEvent);
}

void SeedMenu::Update(float deltaTime)
{
    for (auto &p : packets)
    {
        if (p.ready < p.recharge)
        {
            p.ready += deltaTime;
            if (p.ready > p.recharge)
                p.ready = p.recharge;
        }
    }
}

bool SeedMenu::CanPlantSelected() const
{
    if (selected < 0)
        return false;

    const auto &p = packets[selected];
    return p.ready >= p.recharge && bank.Get() >= p.cost;
}

void SeedMenu::ConsumeSelected()
{
    if (selected < 0)
        return;

    packets[selected].ready = 0.f;
}

void SeedMenu::OnInput(int input)
{
    if (input == '1')
        selected = 0;
    else if (input == '2')
        selected = 1;
    else if (input == '3')
        selected = 2;
}
