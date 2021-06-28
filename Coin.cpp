#include "Coin.h"


Coin::Coin()
{
}

Coin::Coin(int amount, int quantity)
{
	this->setCoin(amount, quantity);
}

Coin::~Coin()
{
}

int Coin::getAmount()
{
	return this->amount;
}

void Coin::setAmount(int amount)
{
	this->amount = amount;
}

int Coin::getQuantity()
{
	return this->quantity;
}

void Coin::setQuantity(int quantity)
{
	this->quantity = quantity;
}

void Coin::setCoin(int amount, int quantity)
{
	this->amount = amount;
	this->quantity = quantity;
}
