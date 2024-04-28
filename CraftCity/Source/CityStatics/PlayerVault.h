#pragma once
class PlayerVault
{
public:
	int GetMoneyAmount() const;
	void SpendMoney(int moneyAmount);
	void EarnMoney(int moneyAmount);
private:
	int money = 100;
};

