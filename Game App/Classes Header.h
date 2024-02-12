#pragma once
#include "iostream"
#include "vector"
using namespace std;


class Board
{
protected:
	vector<vector<char>> Grid;
	int n_moves;
	bool equal(char first, char second, char third)
	{
		if (first == ' ')
			return false;
		if (first == second && first == third && second == third)
			return true;

		return false;
	}
public:
	virtual bool update_board(int x, int y, char sympol) = 0;
	virtual void display_board() = 0;
	virtual bool is_win() = 0;
	virtual bool is_draw() = 0;
	virtual bool game_over() = 0;
	virtual int minimax(int &x, int &y, int depth, int order, bool firstTime = true) = 0;
};

class XO_Board: public Board
{
private:
	int status();
public:
	XO_Board();
	bool update_board(int x, int y, char sympol);
	void display_board();
	bool is_win();
	bool is_draw();
	bool game_over();
	int minimax(int& x, int& y, int depth, int order, bool firstTime = true);
};

class Pyramic_Board : public Board
{
private:
	int status();
public:
	Pyramic_Board();
	bool update_board( int x,  int y,  char sympol);
	void display_board();
	bool is_win();
	bool is_draw();
	bool game_over();
	int minimax(int& x, int& y, int depth, int order, bool firstTime = true);
};

class Connect4_Board: public Board
{
private:
	int status();
public:
	Connect4_Board();
 	bool update_board(const int x, const int y, const char sympol);
	void display_board();
	bool is_win();
	bool is_draw();
	bool game_over();
	int minimax(int& x, int& y, int depth, int order, bool firstTime = true);
};

class FiveFive_Board : public Board
{
private:
	int p1_point, p2_point;
	void update_points();
	int status();
public:
	FiveFive_Board();
	bool update_board(const int x, const int y, const char sympol);
	void display_board();
	bool is_win();
	bool is_draw();
	bool game_over();
	int minimax(int& x, int& y, int depth, int order, bool firstTime = true);
};


class Player 
{
protected:
	string Name;
	char Symbol;
	int Order;
public:
	Player(string name, char symbol, int order);
	char get_sympol();
	string get_name();
	virtual void get_move(int& x, int& y);
};

class AI_Player:public Player
{
private:
	Board* board;
public:
	AI_Player(Board* board, char symobol, int order); 
	void get_move(int &x, int &y);
};

class Game_Manager
{
private:
	Player *players[2];
	Board *board;
public:
	Game_Manager(Board* B, Player* P[2]);
	void run();
};