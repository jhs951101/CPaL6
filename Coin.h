#pragma once

class Coin
{
	int amount;
	int quantity;

public:
	Coin();
	Coin(int amount, int quantity);
	~Coin();

	int getAmount();
	void setAmount(int amount);

	int getQuantity();
	void setQuantity(int quantity);

	void setCoin(int amount, int quantity);
};

