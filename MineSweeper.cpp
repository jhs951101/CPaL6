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

	for(int i=0; i<height+2; i++)	  // 참고) 테이블의 제일 모서리 쪽은 사용하지 않음
		for(int j=0; j<width+2; j++){
			this->inputTable[i][j] = 'N';  // input테이블 - N: NULL
			this->outputTable[i][j] = '?';  // output테이블을 모두 '?'로 세팅함
		}

	for (int i = 0; i < this->mines; i++){

		int row, column;

		do{
			row = (rand() % this->height) + 1;
			column = (rand() % this->width) + 1;

		}while( inputTable[row][column] == 'B' );

		this->inputTable[row][column] = 'B';
	}										// 지뢰를 임의로 설치함

	for(int x=1; x<=height; x++)
		for(int y=1; y<=width; y++){

			int n = 0;  // n: input테이블에 지뢰의 갯수를 저장하기 위한 변수

			if( this->inputTable[x][y] != 'B' ){  // 해당 위치가 지뢰가 아닐 경우에만 숫자 저장

				if( this->inputTable[x-1][y] == 'B' ) n++;
				if( this->inputTable[x+1][y] == 'B' ) n++;
				if( this->inputTable[x][y-1] == 'B' ) n++;
				if( this->inputTable[x][y+1] == 'B' ) n++;

				if( this->inputTable[x-1][y-1] == 'B' ) n++;
				if( this->inputTable[x+1][y+1] == 'B' ) n++;
				if( this->inputTable[x-1][y+1] == 'B' ) n++;
				if( this->inputTable[x+1][y-1] == 'B' ) n++;
					// 8가지 방향 모두 수색해서 n의 값을 설정함

				this->inputTable[x][y] = n + '0';  // input테이블에 숫자(n)를 투입
			}
		}
}

// If the mine exists in the current position with row and column, it returns true.
// Otherwise, it returns false.
bool MineSweeper::checkInputTable(int row, int column)
{
	if( this->inputTable[row][column] == 'B' ) return true;  // 해당 위치에 지뢰가 존재할 경우
	else return false;
}

// Depending on the mark_option, update the output table.
// If the mark_option is 1, the current position is set to '*'.
// Otherwise, you update the current position.
// If the current position is '0', we also update adjacent positions in a recursive way.
void MineSweeper::updateOutputTable(int row, int column, int mark_option)
{
	if(mark_option == 1){  // mark_option 이 1이면 해당 위치에 '*'을 저장
		
		this->outputTable[row][column] = '*';
		this->mark++;

		if( this->inputTable[row][column] == 'B' ) this->correct++;
		  // 지뢰가 있는 곳에 *을 박았을 경우 correct를 +1 시킴
	}
	else if( this->inputTable[row][column] > '0' ){  // 해당 위치에 양수의 숫자가 존재할 경우

		if( this->inputTable[row][column] == 'B' && this->outputTable[row][column] == '*'){
			this->correct--;  // 지뢰가 있는 곳인데 *을 없앴을 경우 correct, mark 를 -1 시킴
			this->mark--;

		} else if( this->outputTable[row][column] == '*' )
			this->mark--;  // *을 없앴을 경우 mark 를 -1 시킴

		this->outputTable[row][column] = this->inputTable[row][column];  // 해당 위치의 숫자만 공개함
	}
	else{  // 해당 위치가 0일 경우 Area처럼 숫자를 공개해야함

		int table2[8+2][6+2] = { 0 };  // table2: '*'이 저절로 지위지지 않도록 하기 위한 배열

		if(mark_option == 0){	// (재귀함수에서는 진행X)
								// 참고1) mark_option 이 0이면 일반 함수 (5이면 재귀 함수)
								// 참고2) mark_option 의 값에 따라 재귀 함수인지 아닌지를 구분

			if( this->outputTable[row][column] == '*' ){

				this->outputTable[row][column] = this->inputTable[row][column];
				this->mark--;
			}										  // *을 없앴을 경우 mark 를 -1 시킴

			for(int x=1; x<=height; x++)
				for(int y=1; y<=width; y++)
					if( this->outputTable[x][y] == '*') table2[x][y] = '*';
						// out테이블에 있는 모든 '*'을 옮겨줌
		}		

		this->outputTable[row][column] = this->inputTable[row][column];  // 해당 위치를 공개함 

		for(int a=1; a<=8; a++){

			int x = row;     // x: 행 제어
			int y = column;  // y: 열 제어

			this->inputTable[row][column] = 'X';  // 우선 해당 위치를 'X'라고 놓고 수색을 시작함
												  // 재귀 함수 무한 진행을 막기 위해 사용

			if(a == 1) { y--; }			   // 수색 방향: ←
			else if(a == 2) { x--; y--; }  // 수색 방향: ↖
			else if(a == 3) { x--; }	   // 수색 방향: ↑
			else if(a == 4) { x--; y++; }  // 수색 방향: ↗
			else if(a == 5) { y++; }	   // 수색 방향: →
			else if(a == 6) { x++; y++; }  // 수색 방향: ↘
			else if(a == 7) { x++; }	   // 수색 방향: ↓
			else if(a == 8) { x++; y--; }  // 수색 방향: ↙
				// a의 값에 따라 수색 방향을 달리함
				// 시계 방향으로 수색을 진행
				
			this->outputTable[x][y] = this->inputTable[x][y];  // 수색 방향으로 바뀐 위치를 공개함
					
			if( this->inputTable[x][y] == '0')
				updateOutputTable(x, y, 5);  // 수색하다 '0'이 발견되었을 경우 재귀함수 진행
		}

		if(mark_option == 0){  // (재귀함수에서는 진행X)

			for(int x=1; x<=height; x++){
				for(int y=1; y<=width; y++){
					if( this->outputTable[x][y] == 'X') this->outputTable[x][y] = '0';
					if( this->inputTable[x][y] == 'X') this->inputTable[x][y] = '0';
						// 테이블에 있는 모든 'X'를 0으로 바꿔줌
				}
			}

			for(int x=1; x<=height; x++)
				for(int y=1; y<=width; y++)
					if(table2[x][y] == '*') this->outputTable[x][y] = '*';
						// 저장했던 '*'을 다시 out테이블로 넘겨줌
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