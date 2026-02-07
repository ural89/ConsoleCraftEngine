#include "EnemyAmeboid.h"
#include "../../Components/Health.h"
void EnemyAmeboid::Init()
{
    EnemyRogue::Init();
    GetComponent<Health>()->AddHealth(1); //Start with 2 healths
    symbol = '-';
    std::string symbol00 = "_";
    std::string symbol01 = "|";
    symbols.push_back(symbol00);
    symbols.push_back(symbol01);
    Sprite sprite00 = {
        {1, 1, 1, 1, 1},
        {1, 2, 1, 2, 1},
        {1, 1, 1, 1, 1},
        {1, 5, 1, 5, 1},
       };
    Sprite sprite01 = {
           {1, 1, 1, 1, 1},
           {1, 2, 1, 2, 1},
           {1, 1, 1, 1, 1},
           {1, 1, 1, 1, 1},
            };
    sprites.push_back(sprite00);
    sprites.push_back(sprite01);
}

void EnemyAmeboid::Update(float deltaTime)
{
    EnemyRogue::Update(deltaTime);
}

void EnemyAmeboid::OnMove()
{
    animationIndex++;
    animationIndex = animationIndex % sprites.size();
   
	symbol = symbols[animationIndex];
	Sprite sprite = sprites[animationIndex];
    SetSprite(sprite);

}
