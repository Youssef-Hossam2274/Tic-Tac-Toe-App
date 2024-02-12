#include "Classes Header.h"

AI_Player::AI_Player(Board* boardptr, char symbol, int order): Player("AI Player", symbol, order)
{
	board = boardptr;
}

void AI_Player::get_move(int& x, int& y)
{
	board->minimax(x, y, 5, 2);
	cout << "AI play in coordinate (" << x << ", " << y << ").\n";
}

