#pragma once

#include "Beverage.h"
#include "Coin.h"

class VendingMachine
{
private:
	int earnedMoney;
	int totalChanges;
	int totalBeverageQuantity;

	Beverage beverages[5];	// Coke, Sprite, Fanta, Orange juice, Water
	Coin coins[4];	// 10, 50, 100, 500 won

	// If your money exceeds the current total or it is smaller than 400 won, 
	// Show the messsage to ask the user to input the money again.
	int insertMoney();

	// Show the option to choose the beverage.
	// If the quantify of the chosen beverage is 0, ask the user to choose another beverage.
	int chooseBeverage(int money);

	// Update the status of coins and beverages.
	// If the chanage exists, give the user the change with the smallest quantity.
	void updateMoney(int money, int beverage);

	void showEarnedMonery();
	void showBeverageStatus();
	void showCoinStatus();

public:
	VendingMachine();
	~VendingMachine();

	void displayVendingMachine();
};

