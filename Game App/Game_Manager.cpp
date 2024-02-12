#include "Classes Header.h"


Game_Manager::Game_Manager(Board* B, Player* P[2])
{
	board = B;
	players[0] = P[0];
	players[1] = P[1];
}

void Game_Manager::run()
{
	int x = -1, y = -1;
	
	board->display_board();
	while (true)
	{
		for (int i : {0, 1})
		{
			players[i]->get_move(x, y);
			while(!board->update_board(x, y, players[i]->get_sympol()))
				players[i]->get_move(x, y);

			board->display_board();
			if (board->is_win())
			{
				cout << "The player " << players[i]->get_name() << " with symbol " << players[i]->get_sympol() << " is win!\n";
				return;
			}
			else if (board->is_draw())
			{
				cout << "Draw!\n";
				return;
			}
		}
	}
}
