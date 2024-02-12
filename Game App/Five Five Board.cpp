#include <algorithm>
#include "Classes Header.h"

void FiveFive_Board::update_points()
{
	p1_point = 0, p2_point = 0;
	for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			if (i < 3 && equal(Grid[i][j], Grid[i + 1][j], Grid[i + 2][j]))
				(Grid[i][j] == 'X' ? p1_point++ : p2_point++);       // check for colmns

			if (j < 3 && equal(Grid[i][j], Grid[i][j + 1], Grid[i][j + 2]))
				(Grid[i][j] == 'X' ? p1_point++ : p2_point++);      // check for rows
			
			if (i < 3 && j < 3 &&
				equal(Grid[i][j], Grid[i + 1][j + 1], Grid[i + 2][j + 2]))
				(Grid[i][j] == 'X' ? p1_point++ : p2_point++);      // check for down right diag
			
			if (i < 3 && j > 1 &&
				equal(Grid[i][j], Grid[i + 1][j - 1], Grid[i + 2][j - 2]))
				(Grid[i][j] == 'X' ? p1_point++ : p2_point++);      // check for down left diag
		}
	}
}

int FiveFive_Board::status()
{
	//if (n_moves != 24)
	//	return 1;
	if (n_moves == 24)
		return 3333;            // game is over 
	if (p1_point > p2_point)
		return p1_point;
	if (p2_point > p1_point)
		return (p2_point * -1);
	if (p1_point == p2_point)
		return 0;
}

FiveFive_Board::FiveFive_Board():p1_point(0), p2_point(0)
{
	
	Grid.resize(5);
	for (int i = 0; i < 5; ++i)
	{
		Grid[i].resize(5);
		fill(Grid[i].begin(), Grid[i].end(), ' ');
	}
}

bool FiveFive_Board::update_board(const int x, const int y, const char symbol)
{
	if (x > 5 || x < 0 || y > 5 || y < 0)
	{
		cout << "invalid coordinate\n";
		return false;
	}

	else if (Grid[x][y] != ' ')
	{
		cout << "invalid place, someone play here.\n";
		return false;
	}
	Grid[x][y] = symbol;
	n_moves++;
	update_points();
	return true;
}

void FiveFive_Board::display_board()
{
	cout << "\nX has a " << p1_point << " points" << "\t\t" << "O has a " << p2_point << " points\n";
	for (int i = 0; i < Grid.size(); ++i)
	{
		for (int j = 0; j < Grid[0].size(); ++j)
		{
			if (j)
				cout << "|  ";
			if (Grid[i][j] == ' ')
				cout << '(' << i << ", " << j << ')' << "  ";
			else
				cout << "   " << Grid[i][j] << "    ";
		}
		cout << '\n';
	}
}

bool FiveFive_Board::is_win()
{
	bool win = false;
	if (n_moves == 24 && p1_point > p2_point)
		win = true;
	else if (n_moves == 24 && p1_point < p2_point)
		return true;
	
	if (win)
	{
		cout << "X has a " << p1_point << " points" << "\t\t" << "O has a " << p2_point << " points\n";
		return true;
	}
	return false;
	
	//int StatusNum = status();
	//if (StatusNum == 2 || StatusNum == -2)
	//{
	//	cout << "X has a " << p1_point << " points" << "\t" << "O has a " << p2_point << " points\n";
	//	return true;
	//}
	//return false;
}

bool FiveFive_Board::is_draw()
{
	if (n_moves == 24 && p1_point == p2_point)
	{
		cout << "X has a " << p1_point << " points" << "\t" << "O has a " << p2_point << " points\n";
		return true;
	}
	return false;
}

bool FiveFive_Board::game_over()
{
	return (n_moves == 24);
}

int FiveFive_Board::minimax(int& x, int& y, int depth, int order, bool firstTime)
{
	int statusNum = status();
	if ( depth == 0)
		return statusNum;

	int minScore = INT_MAX, maxScore = INT_MIN;
	int final_i = 0, final_j= 0;
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; ++j)
		{
			if (Grid[i][j] == ' ')
			{
				if (order == 1)   // x turn
				{
					Grid[i][j] = 'X';
					update_points();
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
					update_points();
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
