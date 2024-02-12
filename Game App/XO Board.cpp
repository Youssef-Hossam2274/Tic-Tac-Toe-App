#include "Classes Header.h"
#include <algorithm>

int XO_Board::status()
{
	//0  -> Draw
	//2  -> X win
	//-2 -> O win
	//1  -> Otherwise

	for (int i = 0; i < 3; ++i)
	{
		if (equal(Grid[i][0], Grid[i][1], Grid[i][2]))          // check for rows
			return (Grid[i][0] == 'X' ? 2 : -2);
		else if (equal(Grid[0][i], Grid[1][i], Grid[2][i]))      // check for cols
			return (Grid[0][i] == 'X' ? 2 : -2);
	}
	if (equal(Grid[0][0], Grid[1][1], Grid[2][2]) ||           // check for diag
		equal(Grid[0][2], Grid[1][1], Grid[2][0]))
			return (Grid[1][1] == 'X' ? 2 : -2);

	if (this->is_draw())
		return 0;
	return 1;
}

XO_Board::XO_Board()
{
	n_moves = 0;
	Grid.resize(3);
	
	for (int i = 0; i < 3; ++i)
	{
		Grid[i].resize(3);
		fill(Grid[i].begin(), Grid[i].end(), ' ');
	}
}

bool XO_Board::update_board(int x, int y, char symbol)
{
	if (x > 3 || x < 0 || y > 3 || y < 0 )
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
	return true;
}

void XO_Board::display_board()
{
	for (int i = 0; i < Grid.size(); ++i)
	{
		for (int j = 0; j < Grid[0].size(); ++j)
		{
			if (j)
				cout << "|   ";
			if (Grid[i][j] == ' ')
				cout << '(' << i << ", " << j << ')' << "   ";
			else
				cout << "   " << Grid[i][j] << "     ";
		}
		cout << '\n';
	}

}

bool XO_Board::is_win()
{
	int flag = status();
	
	if (flag == 2 || flag == -2)
		return true;
	return false;
}

bool XO_Board::is_draw()
{
	return (n_moves == 9);
}

bool XO_Board::game_over()
{
	return (this->is_draw() || this->is_win());
}

int XO_Board::minimax(int& x, int& y, int depth, int order, bool firstTime)
{
	int statusNum = status();
	if (statusNum != 1)
		return statusNum;
	
	int minScore = INT_MAX, maxScore = INT_MIN;
	int final_i, final_j;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; ++j)
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
