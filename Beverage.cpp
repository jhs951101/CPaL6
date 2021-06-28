#include "Beverage.h"


Beverage::Beverage()
{

}


Beverage::Beverage(string name, int price, int quantity)
{
	this->setBeverage(name, price, quantity);
}


Beverage::~Beverage()
{
}

string Beverage::getName()
{
	return this->name;
}

void Beverage::setName(string name)
{
	this->name = name;
}
	
int Beverage::getPrice()
{
	return this->price;
}

void Beverage::setPrice(int price)
{
	this->price = price;
}


int Beverage::getQuantity()
{
	return this->quantity;
}

void Beverage::setQuantity(int quantity)
{
	this->quantity = quantity;
}

void Beverage::setBeverage(string name, int price, int quantity)
{
	this->name = name;
	this->price = price;
	this->quantity = quantity;
}


void Beverage::updateQuantity()
{
	this->quantity--;
}

