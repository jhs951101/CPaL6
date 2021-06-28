#pragma once

#include <string>

using namespace std;

class Beverage
{
private:
	string name;
	int price;
	int quantity;

public:
	Beverage();
	Beverage(string name, int price, int quantity);
	~Beverage();

	string getName();
	void setName(string name);
	int getPrice();
	void setPrice(int price);
	int getQuantity();
	void setQuantity(int quantity);

	void setBeverage(string name, int price, int quantity);
	void updateQuantity(); // Decrease the quanity by 1.
};

