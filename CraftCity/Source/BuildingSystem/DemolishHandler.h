#pragma once

class DemolishHandler
{
public:
    DemolishHandler(class CityStatics& CityStatics) : cityStatics(cityStatics)
    {

    }
    void Demolish(class GameObject& gameObject);

private:
    CityStatics& cityStatics;
};