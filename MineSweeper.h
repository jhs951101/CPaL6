#pragma once
class MineSweeper
{
private:
	int width;
	int height;
	int mines;		// The number of mines
	char** inputTable;

	int mark;		// The number of marks
	int correct;	// Variable to check if your marking position is correct.
	char** outputTable;

	// Initialize the input table where the mines are randomly positioned.
	// Initialize the input table where all positions are '?'.
	void initializeTable();

	// If the mine exists in the current position with row and column, it returns true.
	// Otherwise, it returns false.
	bool checkInputTable(int row, int column);

	// Depending on the mark_option, update the output table.
	// If the mark_option is 1, the current position is set to '*'.
	// Otherwise, you update the current position.
	// If the current position is '0', we also update adjacent positions in a recursive way.
	void updateOutputTable(int row, int column, int mark_option);

	// Print the output table.
	void printOutputTable();

public:
	MineSweeper();
	MineSweeper(int width, int height, int mines);
	~MineSweeper();

	void startMineSweeper();
};

