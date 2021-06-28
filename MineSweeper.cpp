#include "MineSweeper.h"
#include <iostream>
#include <ctime>

using namespace std;

MineSweeper::MineSweeper()
{
	this->height = 8;
	this->width = 6;
	this->mines = 10;
	this->mark = 0;
	this->correct = 0;

	this->inputTable = new char*[this->height + 2];
	for (int i = 0; i <= this->height + 1; i++)
		this->inputTable[i] = new char[this->width + 2];

	this->outputTable = new char*[this->height + 2];
	for (int i = 0; i <= this->height + 1; i++)
		this->outputTable[i] = new char[this->width + 2];
}


MineSweeper::MineSweeper(int width, int height, int mines)
{
	this->height = height;
	this->width = width;
	this->mines = mines;
	this->mark = 0;
	this->correct = 0;

	this->inputTable = new char*[this->height + 2];
	for (int i = 0; i <= this->height + 1; i++)
		this->inputTable[i] = new char[this->width + 2];

	this->outputTable = new char*[this->height + 2];
	for (int i = 0; i <= this->height + 1; i++)
		this->outputTable[i] = new char[this->width + 2];
}


MineSweeper::~MineSweeper()
{
	for (int i = 0; i <= this->height + 1; i++)
		delete[] this->inputTable[i];
	delete[] this->inputTable;

	for (int i = 0; i <= this->height + 1; i++)
		delete[] this->outputTable[i];
	delete[] this->outputTable;
}


void MineSweeper::startMineSweeper()
{

	while (true)
	{
		int option ;
		cout << "Do you want to play the MineSweeper? (1: Yes, 0: Quit) ";
		cin >> option;

		if (option == 1)
		{
			// Initialize the input table with random mine positions and the output table with '?'
			this->initializeTable();


			while (true)
			{
				// Input your position.
				int row, column;
				cout << "Input the your position (row, column): ";
				cin >> row >> column;

				
				// Ask if you want to mark the sweeper.
				int mark_option;
				while (true)
				{
					cout << "Do you want to mark the sweeper (1: Yes, 0: No): ";
					cin >> mark_option;

					if (mark_option == 0 || (mark_option == 1 && this->mark < this->mines))
						break;
				}

				// Check if the current position has a mine.
				bool isMine = false;
				if (mark_option == 0)
					isMine = this->checkInputTable(row, column);

				// Update the status of the output table.
				// If the current position is '0', update the adjacent positions.
				if (!isMine)
				{
					updateOutputTable(row, column, mark_option);
					printOutputTable();
				}

				// Check the game termination conditions.
				if (isMine)
				{
					cout << "Bomb!!! Game over!!" << endl;
					break;
				}
				else if (this->correct == this->mines)
				{
					cout << "You found all mines!! You win! " << endl;
					break;
				}
				else if (this->mark == this->mines)
				{
					cout << "Some mines have wrong positions!! You lose! " << endl;
					break;
				}
			}
		}
		else if (option == 0)
			break;
		else
			continue;
	}
}

// Initialize the input table where the mines are randomly positioned.
// Initialize the output table where all positions are '?'.
void MineSweeper::initializeTable()
{
	srand((unsigned)time(NULL));

	for(int i=0; i<height+2; i++)	  // ����) ���̺��� ���� �𼭸� ���� ������� ����
		for(int j=0; j<width+2; j++){
			this->inputTable[i][j] = 'N';  // input���̺� - N: NULL
			this->outputTable[i][j] = '?';  // output���̺��� ��� '?'�� ������
		}

	for (int i = 0; i < this->mines; i++){

		int row, column;

		do{
			row = (rand() % this->height) + 1;
			column = (rand() % this->width) + 1;

		}while( inputTable[row][column] == 'B' );

		this->inputTable[row][column] = 'B';
	}										// ���ڸ� ���Ƿ� ��ġ��

	for(int x=1; x<=height; x++)
		for(int y=1; y<=width; y++){

			int n = 0;  // n: input���̺� ������ ������ �����ϱ� ���� ����

			if( this->inputTable[x][y] != 'B' ){  // �ش� ��ġ�� ���ڰ� �ƴ� ��쿡�� ���� ����

				if( this->inputTable[x-1][y] == 'B' ) n++;
				if( this->inputTable[x+1][y] == 'B' ) n++;
				if( this->inputTable[x][y-1] == 'B' ) n++;
				if( this->inputTable[x][y+1] == 'B' ) n++;

				if( this->inputTable[x-1][y-1] == 'B' ) n++;
				if( this->inputTable[x+1][y+1] == 'B' ) n++;
				if( this->inputTable[x-1][y+1] == 'B' ) n++;
				if( this->inputTable[x+1][y-1] == 'B' ) n++;
					// 8���� ���� ��� �����ؼ� n�� ���� ������

				this->inputTable[x][y] = n + '0';  // input���̺� ����(n)�� ����
			}
		}
}

// If the mine exists in the current position with row and column, it returns true.
// Otherwise, it returns false.
bool MineSweeper::checkInputTable(int row, int column)
{
	if( this->inputTable[row][column] == 'B' ) return true;  // �ش� ��ġ�� ���ڰ� ������ ���
	else return false;
}

// Depending on the mark_option, update the output table.
// If the mark_option is 1, the current position is set to '*'.
// Otherwise, you update the current position.
// If the current position is '0', we also update adjacent positions in a recursive way.
void MineSweeper::updateOutputTable(int row, int column, int mark_option)
{
	if(mark_option == 1){  // mark_option �� 1�̸� �ش� ��ġ�� '*'�� ����
		
		this->outputTable[row][column] = '*';
		this->mark++;

		if( this->inputTable[row][column] == 'B' ) this->correct++;
		  // ���ڰ� �ִ� ���� *�� �ھ��� ��� correct�� +1 ��Ŵ
	}
	else if( this->inputTable[row][column] > '0' ){  // �ش� ��ġ�� ����� ���ڰ� ������ ���

		if( this->inputTable[row][column] == 'B' && this->outputTable[row][column] == '*'){
			this->correct--;  // ���ڰ� �ִ� ���ε� *�� ������ ��� correct, mark �� -1 ��Ŵ
			this->mark--;

		} else if( this->outputTable[row][column] == '*' )
			this->mark--;  // *�� ������ ��� mark �� -1 ��Ŵ

		this->outputTable[row][column] = this->inputTable[row][column];  // �ش� ��ġ�� ���ڸ� ������
	}
	else{  // �ش� ��ġ�� 0�� ��� Areaó�� ���ڸ� �����ؾ���

		int table2[8+2][6+2] = { 0 };  // table2: '*'�� ������ �������� �ʵ��� �ϱ� ���� �迭

		if(mark_option == 0){	// (����Լ������� ����X)
								// ����1) mark_option �� 0�̸� �Ϲ� �Լ� (5�̸� ��� �Լ�)
								// ����2) mark_option �� ���� ���� ��� �Լ����� �ƴ����� ����

			if( this->outputTable[row][column] == '*' ){

				this->outputTable[row][column] = this->inputTable[row][column];
				this->mark--;
			}										  // *�� ������ ��� mark �� -1 ��Ŵ

			for(int x=1; x<=height; x++)
				for(int y=1; y<=width; y++)
					if( this->outputTable[x][y] == '*') table2[x][y] = '*';
						// out���̺� �ִ� ��� '*'�� �Ű���
		}		

		this->outputTable[row][column] = this->inputTable[row][column];  // �ش� ��ġ�� ������ 

		for(int a=1; a<=8; a++){

			int x = row;     // x: �� ����
			int y = column;  // y: �� ����

			this->inputTable[row][column] = 'X';  // �켱 �ش� ��ġ�� 'X'��� ���� ������ ������
												  // ��� �Լ� ���� ������ ���� ���� ���

			if(a == 1) { y--; }			   // ���� ����: ��
			else if(a == 2) { x--; y--; }  // ���� ����: ��
			else if(a == 3) { x--; }	   // ���� ����: ��
			else if(a == 4) { x--; y++; }  // ���� ����: ��
			else if(a == 5) { y++; }	   // ���� ����: ��
			else if(a == 6) { x++; y++; }  // ���� ����: ��
			else if(a == 7) { x++; }	   // ���� ����: ��
			else if(a == 8) { x++; y--; }  // ���� ����: ��
				// a�� ���� ���� ���� ������ �޸���
				// �ð� �������� ������ ����
				
			this->outputTable[x][y] = this->inputTable[x][y];  // ���� �������� �ٲ� ��ġ�� ������
					
			if( this->inputTable[x][y] == '0')
				updateOutputTable(x, y, 5);  // �����ϴ� '0'�� �߰ߵǾ��� ��� ����Լ� ����
		}

		if(mark_option == 0){  // (����Լ������� ����X)

			for(int x=1; x<=height; x++){
				for(int y=1; y<=width; y++){
					if( this->outputTable[x][y] == 'X') this->outputTable[x][y] = '0';
					if( this->inputTable[x][y] == 'X') this->inputTable[x][y] = '0';
						// ���̺� �ִ� ��� 'X'�� 0���� �ٲ���
				}
			}

			for(int x=1; x<=height; x++)
				for(int y=1; y<=width; y++)
					if(table2[x][y] == '*') this->outputTable[x][y] = '*';
						// �����ߴ� '*'�� �ٽ� out���̺�� �Ѱ���
		}
	
	}

}

// Print the output table.
void MineSweeper::printOutputTable()
{
	for(int x=1; x<=height; x++){
		for(int y=1; y<=width; y++)
			cout << this->outputTable[x][y] << " ";

		cout << endl;
	}
	cout << endl;
}