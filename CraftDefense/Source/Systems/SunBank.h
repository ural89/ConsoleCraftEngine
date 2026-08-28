#pragma once

class SunBank
{
public:
    int Get() const { return sun; }
    void Spend(int amount) { sun -= amount; }
    void Earn(int amount) { sun += amount; }

private:
    int sun = 50;
};
