#pragma once
#include <algorithm>
#include "Classes Header.h"


int Pyramic_Board::status()
{
	//0  -> Draw
	//2  -> X win
	//-2 -> O win
	//1  -> Otherwise
	
	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 3; ++j)
			if (equal(Grid[i][j], Grid[i][j + 1], Grid[i][j + 2]))          // check for rows
				return (Grid[i][j] == 'X' ? 2 : -2);

	if (equal(Grid[0][2], Grid[1][1], Grid[2][0]) ||           // check for diag
		equal(Grid[0][2], Grid[1][3], Grid[2][4]))
		return (Grid[0][2] == 'X' ? 2 : -2);
	else if (equal(Grid[0][2], Grid[1][2], Grid[2][2]))      // check for cols
		return (Grid[0][2] == 'X' ? 2 : -2);

	if (this->is_draw())
		return 0;
	return 1;
}

Pyramic_Board::Pyramic_Board()
{
	Grid.resize(3);
	for (int i = 0; i < 3; ++i)
	{
		Grid[i].resize(5);
		fill(Grid[i].begin(), Grid[i].end(), ' ');
		for (int j = 0; j < 2 - i; ++j)
			Grid[i][j] = 'W', Grid[i][5 - j - 1] = 'W';
	}
}

bool Pyramic_Board::update_board(const int x, const int y, const char symbol)
{
	if (x > 3 || x < 0 || y > 5 || y < 0)
	{
		cout << "invalid coordinate\n";
		return false;
	}
	else if (Grid[x][y] == 'W')
	{
		cout << "invalid place, please choose from the available places.\n";
		return false;
	}
	else if (Grid[x][y] != ' ')
	{
		cout << "invalid place, someone play here.\n";
		return false;
	}
	Grid[x][y] = symbol;
	n_moves++;
	return true;
}

void Pyramic_Board::display_board()
{
	for (int i = 0; i < Grid.size(); ++i)
	{
		for (int j = 0; j < Grid[0].size(); ++j)
		{
			if (Grid[i][j] == 'W')
				cout << "             ";
			else if (j && Grid[i][j-1] != 'W')
				cout << "|   ";
			if (Grid[i][j] == ' ')
				cout << '(' << i << ", " << j << ')' << "   ";
			else if (Grid[i][j] != 'W')
				cout << "   " << Grid[i][j] << "     ";
		}
		cout << '\n';
	}
}

bool Pyramic_Board::is_win()
{
	int StatusNum = status();
	if (StatusNum == 2 || StatusNum == -2)
		return true;
	return false;
}

bool Pyramic_Board::is_draw()
{
	return (n_moves == 9);
}

bool Pyramic_Board::game_over()
{
	return (this->is_draw() || this->is_win());
}

int Pyramic_Board::minimax(int& x, int& y, int depth, int order, bool firstTime)
{
	int statusNum = status();
	if (statusNum != 1)
		return statusNum;

	int minScore = INT_MAX, maxScore = INT_MIN;
	int final_i, final_j;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 5; ++j)
		{
			if (Grid[i][j] == ' ')
			{
				if (order == 1)   // x turn
				{
					Grid[i][j] = 'X';
					n_moves++;
					int score = minimax(x, y, depth - 1, 2, false);
					Grid[i][j] = ' ';
					n_moves--;
					if (maxScore < score)
					{
						maxScore = score;
						final_i = i;
						final_j = j;
					}
					if (firstTime)
						cout << "the cordinate " << i << ' ' << j << " has a score " << score << '\n';

				}
				else if (order == 2)              // o turn
				{
					Grid[i][j] = 'O';
					n_moves++;
					int score = minimax(x, y, depth - 1, 1, false);
					Grid[i][j] = ' ';
					n_moves--;
					if (minScore > score)
					{
						minScore = score;
						final_i = i;
						final_j = j;
					}
					if (firstTime)
						cout << "the cordinate " << i << ' ' << j << " has a score " << score << '\n';
				}
			}
		}
	}

	if (firstTime)
		x = final_i, y = final_j;

	if (order == 1)
		return maxScore;
	return minScore;
}
