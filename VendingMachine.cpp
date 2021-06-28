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
	int in_money;  // in_money: ����ڰ� ������ ��

	do{
		cout << "Insert your money <max: " << this->totalChanges << "> ";
		cin >> in_money;  // ���� �����ϵ��� ����

		if(in_money > this->totalChanges){  // ���� �� ���� �� �ܾ��� �ʰ����� ��� ������ ��û

			cout << "Money you inserted exceed maximum!" << endl;
			cout << "Insert your money again!" << endl;
		}
		else if(in_money < 400){  // ���� �� ���� \400 �̸��� ��� ������ ��û

			cout << "Money you inserted is short!" << endl;
			cout << "Insert your money again!" << endl;
		}

	}while(in_money > 66000 || in_money < 400);  // �������� ����Ǿ� �ϹǷ� do~while�� ���

	return in_money;
}

// Show the option to choose the beverage.
// If the quantify of the chosen beverage is 0, ask the user to choose another beverage.
int VendingMachine::chooseBeverage(int in_money)
{
	int b_type;   // b_tyle: ����� ����(0: Coke, 1: Sprite, 2: Fanta, 3: OrangeJuice, 4: Water)
	int b_num;    // b_num: ������� ����
	int b_price;  // b_price: ������� ����

	cout << "Choose your beverage" << endl;

	do{
		cout << "0: Coke, 1: Sprite, 2: Fanta, 3: OrangeJuice, 4: Water: ";
		cin >> b_type;  // ������� �����ϰ� ����

		b_num = beverages[b_type].getQuantity();  // ������ ������� ������ ������
		b_price = beverages[b_type].getPrice();  // ������ ������� ���ݸ� ������

		if(b_num <= 0){  // ������ ������� �� �������� ��� �缱�� ��û

			cout << "A Beverage you selected is empty!" << endl;
			cout << "Choose your beverage again!" << endl;
		} else if( in_money < b_price ){  // ���� ����� ������ ������ ��� �缱�� ��û

			cout << "Money you inserted is short!" << endl;
			cout << "Choose your beverage again!" << endl;
		}

	}while(b_num <= 0 || in_money < b_price);  // �缱���� ����Ǿ� �ϹǷ� do~while�� ���

	cout << "Here is your beverage" << endl;

	return b_type;
}

// Update the status of coins and beverages.
// If the chanage exists, give the user the change with the smallest quantity.
void VendingMachine::updateMoney(int money, int beverage)
{
	int b_price;  // b_price: ������ ������� ����
	b_price = beverages[beverage].getPrice();  // ������ ������� ���ݸ� ������

	int r_money = money - b_price;  // r_money: �Ž�����
									// �Ž����� ���

	this->totalChanges -= r_money;  // �� �ܾ��� �Ž�������ŭ ����

	cout << "Your change is " << r_money << endl;

	this->earnedMoney += b_price;  // ���ǱⰡ �� ���� ������� ���ݸ�ŭ ������

	int n = this->beverages[beverage].getQuantity();  // n: ������ ������� ����
													  // ������� ������ ������
	this->beverages[beverage].setQuantity(n-1);  // ������ ������� ������ 1��ŭ ����
	this->totalBeverageQuantity--;

	int i = 3;  // i: return_c[4]�� ��������
	int return_c[4] = { 0 };  // return_c[4]: �Ž����� ������ ���� ����(10, 50, 100, 500)

	while(r_money > 0){  // �Ž������� �������� ��ȯ�ϴ� �κ�

		int c_num = coins[i].getQuantity();  // c_num: ������ ����
		int c_price = coins[i].getAmount();  // c_price: ������ �����ִ� ����(\)

		if(r_money >= c_price && c_num > 0){  // �Ž������� �������� ��ȯ
											  // ��, �ش� ������ �����ؾ���

			return_c[i] += 1;  // �Ž����� ������ +1 ����
			coins[i].setQuantity(c_num - 1);  // �ش� ���� ������ -1 ����
			r_money -= c_price;  // �Ž������� �������� �ٲ� ����ŭ ����
		}
		else i--;  // i�� �����ϸ� ������ �����ִ� ���ڰ� �ٲ�
	}

	for(int i=3; i>=0; i--){

		int c_price = coins[i].getAmount();

		if(return_c[i] > 0){  // �Ž��������� �ش� ������ �����ؾ� ���

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
