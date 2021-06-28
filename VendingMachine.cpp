#include "VendingMachine.h"
#include <iostream>

using namespace std;


VendingMachine::VendingMachine()
{
	this->earnedMoney = 0;
	this->totalChanges = 1000 + 5000 + 10000 + 50000;
	this->totalBeverageQuantity = 50;

	this->beverages[0].setBeverage("Coke", 500, 10);
	this->beverages[1].setBeverage("Sprite", 500, 10);
	this->beverages[2].setBeverage("Fanta", 600, 10);
	this->beverages[3].setBeverage("OrangeJuice", 700, 10);
	this->beverages[4].setBeverage("Water", 400, 10);

	this->coins[0].setCoin(10, 100);
	this->coins[1].setCoin(50, 100);
	this->coins[2].setCoin(100, 100);
	this->coins[3].setCoin(500, 100);
}


VendingMachine::~VendingMachine()
{
}


void VendingMachine::displayVendingMachine()
{
	while (true)
	{
		// Execeptional cases
		if (this->totalChanges < 2000 || this->totalBeverageQuantity <= 10)
			break;

		int option;
		cout << "Choose your option (1: Buy, 0: Quit) ";
		cin >> option;

		if (option == 0)
			break;
		else if (option == 1)
		{
			int money = this->insertMoney();	// Insert your money.
			int beverage = this->chooseBeverage(money);	// Check your beverage.

			// Update earned money and the stauts of beverages.
			// Return the changes. We have to give the changes as efficiently as possible.
			// Update the status of coins.
			this->updateMoney(money, beverage);
		}
		else
			continue;
	}

	// Show the last status of earned money, beverage, and coin.
	this->showEarnedMonery();
	this->showBeverageStatus();
	this->showCoinStatus();
}

// If your money exceeds the current total or it is smaller than 400 won, 
// Show the messsage to ask the user to input the money again.
int VendingMachine::insertMoney()
{
	int in_money;  // in_money: 사용자가 투입한 돈

	do{
		cout << "Insert your money <max: " << this->totalChanges << "> ";
		cin >> in_money;  // 돈을 투입하도록 해줌

		if(in_money > this->totalChanges){  // 투입 한 돈이 총 잔액을 초과했을 경우 재투입 요청

			cout << "Money you inserted exceed maximum!" << endl;
			cout << "Insert your money again!" << endl;
		}
		else if(in_money < 400){  // 투입 한 돈이 \400 미만일 경우 재투입 요청

			cout << "Money you inserted is short!" << endl;
			cout << "Insert your money again!" << endl;
		}

	}while(in_money > 66000 || in_money < 400);  // 재투입이 진행되야 하므로 do~while문 사용

	return in_money;
}

// Show the option to choose the beverage.
// If the quantify of the chosen beverage is 0, ask the user to choose another beverage.
int VendingMachine::chooseBeverage(int in_money)
{
	int b_type;   // b_tyle: 음료수 종류(0: Coke, 1: Sprite, 2: Fanta, 3: OrangeJuice, 4: Water)
	int b_num;    // b_num: 음료수의 갯수
	int b_price;  // b_price: 음료수의 가격

	cout << "Choose your beverage" << endl;

	do{
		cout << "0: Coke, 1: Sprite, 2: Fanta, 3: OrangeJuice, 4: Water: ";
		cin >> b_type;  // 음료수를 선택하게 해줌

		b_num = beverages[b_type].getQuantity();  // 선택한 음료수의 갯수를 저장함
		b_price = beverages[b_type].getPrice();  // 선택한 음료수의 가격를 저장함

		if(b_num <= 0){  // 선택한 음료수가 다 떨어졌을 경우 재선택 요청

			cout << "A Beverage you selected is empty!" << endl;
			cout << "Choose your beverage again!" << endl;
		} else if( in_money < b_price ){  // 돈이 음료수 값보다 부족할 경우 재선택 요청

			cout << "Money you inserted is short!" << endl;
			cout << "Choose your beverage again!" << endl;
		}

	}while(b_num <= 0 || in_money < b_price);  // 재선택이 진행되야 하므로 do~while문 사용

	cout << "Here is your beverage" << endl;

	return b_type;
}

// Update the status of coins and beverages.
// If the chanage exists, give the user the change with the smallest quantity.
void VendingMachine::updateMoney(int money, int beverage)
{
	int b_price;  // b_price: 선택한 음료수의 가격
	b_price = beverages[beverage].getPrice();  // 선택한 음료수의 가격를 저장함

	int r_money = money - b_price;  // r_money: 거스름돈
									// 거스름돈 계산

	this->totalChanges -= r_money;  // 총 잔액을 거스름돈만큼 빼줌

	cout << "Your change is " << r_money << endl;

	this->earnedMoney += b_price;  // 자판기가 번 돈을 음료수의 가격만큼 더해줌

	int n = this->beverages[beverage].getQuantity();  // n: 선택한 음료수의 갯수
													  // 음료수의 갯수를 저장함
	this->beverages[beverage].setQuantity(n-1);  // 선택한 음료수의 갯수를 1만큼 빼줌
	this->totalBeverageQuantity--;

	int i = 3;  // i: return_c[4]의 보조변수
	int return_c[4] = { 0 };  // return_c[4]: 거스름돈 갯수를 각각 저장(10, 50, 100, 500)

	while(r_money > 0){  // 거스름돈을 동전으로 변환하는 부분

		int c_num = coins[i].getQuantity();  // c_num: 동전의 갯수
		int c_price = coins[i].getAmount();  // c_price: 동전에 적혀있는 숫자(\)

		if(r_money >= c_price && c_num > 0){  // 거스름돈을 동전으로 변환
											  // 단, 해당 동전이 존재해야함

			return_c[i] += 1;  // 거스름돈 갯수를 +1 해줌
			coins[i].setQuantity(c_num - 1);  // 해당 동전 갯수를 -1 해줌
			r_money -= c_price;  // 거스름돈을 동전으로 바꾼 값만큼 빼줌
		}
		else i--;  // i가 감소하면 동전에 적혀있는 숫자가 바뀜
	}

	for(int i=3; i>=0; i--){

		int c_price = coins[i].getAmount();

		if(return_c[i] > 0){  // 거스름돈에서 해당 동전이 존재해야 출력

			cout << "The number of " << c_price << " won: ";
			cout << return_c[i] << endl;
		}
	}
}


void VendingMachine::showEarnedMonery()
{
	cout << "Your earned money is " << this->earnedMoney << endl;
}

void VendingMachine::showCoinStatus()
{
	int changeCoin[4] = { 10, 50, 100, 500 };
	for (int i = 0; i < 4; i++)
		cout << "The number of " << changeCoin[i] << " is " << this->coins[i].getQuantity() << endl;
	cout << endl;
}

void VendingMachine::showBeverageStatus()
{
	cout << "The number of Coke is " << this->beverages[0].getQuantity() << endl;
	cout << "The number of Sprite is " << this->beverages[1].getQuantity() << endl;
	cout << "The number of Fanta is " << this->beverages[2].getQuantity() << endl;
	cout << "The number of OrangeJuice is " << this->beverages[3].getQuantity() << endl;
	cout << "The number of Water is " << this->beverages[4].getQuantity() << endl << endl;
}
