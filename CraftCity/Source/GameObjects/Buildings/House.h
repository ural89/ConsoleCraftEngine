#pragma once
#include "Buildable.h"
class House : public Buildable
{
public:
    House(class Scene& scene) : Buildable(scene)
    {
        name = "House";
        Price = 20;
        MaxPeople = 4;
        CurrentPeople = 0;
        Income = 10;

        sprite = {
       {GREEN, GREEN, GREEN, GREEN},
       {GREEN, 0, 0, GREEN},
       {GREEN, 0, 0, GREEN},
       {GREEN, 0, 0, GREEN},
       {GREEN, GREEN, GREEN, GREEN} };
    }

    void Init() override;
    void OnPeriodicTick(int tickPassed) override;

    bool AddPerson() override;
    bool RemovePerson() override;
protected:
    void OnInfrastructureConnected(InfrastructureType) override;
    void OnInfrastructureDisconnected(InfrastructureType) override;

private:
    void UpdateVisualForPeople();
    void CalculatePotentionMaxPeople();
    int potentialMaxPeople = 0;



    
};