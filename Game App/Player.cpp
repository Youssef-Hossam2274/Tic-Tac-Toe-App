#include "Classes Header.h"

Player::Player(string name, char symbol, int order)
{
	Name = name;
	Symbol = symbol;
	Order = order;
}

char Player::get_sympol()
{
	return Symbol;
}

string Player::get_name()
{
	return Name;
}

void Player::get_move(int& x, int& y)
{
	cout << Name << " Please enter the coordinate seperated by space: ";
	cin >> x >> y;
}