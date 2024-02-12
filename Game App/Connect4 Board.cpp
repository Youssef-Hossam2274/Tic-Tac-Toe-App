#include "Classes Header.h"
#include <algorithm>
int Connect4_Board::status()
{
	return 0;
}
Connect4_Board::Connect4_Board()
{
	Grid.resize(6);
	for (int i = 0; i < 6; ++i)
	{
		Grid[i].resize(7);
		fill(Grid[i].begin(), Grid[i].end(), ' ');
	}
}

bool Connect4_Board::update_board(const int x, const int y, const char symbol)
{
	if (x > 7 || x < 0)
	{
		cout << "invalid coordinate\n";
		return false;
	}
	for (int i = 5; i >= 0; --i)
	{
		if (Grid[i][x] == ' ')
		{
			Grid[i][x] = symbol;
			n_moves++;
			return  true;
		}
	}
	cout << "this column is full, please choose any other column.\n";
	return false;
}

void Connect4_Board::display_board()
{
	for (int i = 0; i < 7; ++i)
		cout << "  " << i << ' ';

	cout << '\n';
	for (int i = 0; i < Grid.size(); ++i)
	{
		for (int j = 0; j < Grid[0].size(); ++j)
		{
			if (!j)
				cout << "|";
			cout << " " << (Grid[i][j] == ' ' ? '-': Grid[i][j]) << " |";
		}
		cout << '\n';
	}
	cout << "|___|___|___|___|___|___|___|\n";
}

bool Connect4_Board::is_win()
{
	for (int i = 0; i < 6; ++i)
	{
		for (int j = 0; j < 7; ++j)
		{
			if (i < 3 && equal(Grid[i][j], Grid[i + 1][j], Grid[i + 2][j]) && Grid[i][j] == Grid[i + 3][j])
				return true;       // check for colmns
			else if (j < 4 && equal(Grid[i][j], Grid[i][j + 1], Grid[i][j + 2]) && Grid[i][j] == Grid[i][j + 3])
				return true;      // check for rows
			else if (i < 3 && j < 4 &&
				equal(Grid[i][j], Grid[i + 1][j + 1], Grid[i + 2][j + 2]) && Grid[i][j] == Grid[i + 3][j + 3])
				return true;     // check for down right diag
			else if (i < 3 && j > 2 &&
				equal(Grid[i][j], Grid[i + 1][j - 1], Grid[i + 2][j - 2]) && Grid[i][j] == Grid[i + 3][j - 3])
				return true;     // check for down left diag
		}
	}
	return false;
}

bool Connect4_Board::is_draw()
{
	return (n_moves == 42);
}

bool Connect4_Board::game_over()
{
	return (this->is_draw() || this->is_win());
}

int Connect4_Board::minimax(int& x, int& y, int depth, int order, bool firstTime)
{
	return 0;
}
