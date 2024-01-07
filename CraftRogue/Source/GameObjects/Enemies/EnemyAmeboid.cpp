#include "EnemyAmeboid.h"

void EnemyAmeboid::Init()
{
    EnemyRogue::Init();
    symbol = '-';
    sprite = {
        {1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1}};
}

void EnemyAmeboid::Update(float deltaTime)
{
    EnemyRogue::Update(deltaTime);
}

void EnemyAmeboid::OnMove()
{
    if (symbol == "|")
    {
        symbol = '+';
        sprite = {
            {1, 1, 1, 1, 1, 1},
            {1, 1, 1, 1, 1, 1},
            {1, 1, 1, 1, 1, 1},
            {1, 1, 1, 1, 1, 1},
            {1, 1, 1, 1, 1, 1}};
    }
    else
    {
        symbol = '|';
        sprite = {
            {7, 1, 1, 1, 1, 7},
            {7, 1, 1, 1, 1, 7},
            {7, 1, 1, 1, 1, 7},
            {7, 1, 1, 1, 1, 7},
            {7, 1, 1, 1, 1, 7}};
    }
}
