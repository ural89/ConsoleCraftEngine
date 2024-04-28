#include "PlayerVault.h"

int PlayerVault::GetMoneyAmount() const
{
    return money;
}

void PlayerVault::SpendMoney(int moneyAmount)
{
    money -= moneyAmount;
}

void PlayerVault::EarnMoney(int moneyAmount)
{
    money += moneyAmount;
}
