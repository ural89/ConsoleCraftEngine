#include "EnemyAmeboid.h"

void EnemyAmeboid::Init()
{
    EnemyRogue::Init();
    symbol = '-';
    std::string symbol00 = "_";
    std::string symbol01 = "|";
    symbols.push_back(symbol00);
    symbols.push_back(symbol01);
    std::vector<std::vector<int>> sprite00 = {
        {1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1}};
    std::vector<std::vector<int>> sprite01 = {
           {7, 1, 1, 1, 1, 7},
           {7, 1, 1, 1, 1, 7},
           {7, 1, 1, 1, 1, 7},
           {7, 1, 1, 1, 1, 7},
           {7, 1, 1, 1, 1, 7} };
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
	sprite = sprites[animationIndex];

}
