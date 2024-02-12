#include <iostream>
#include "Classes Header.h"
using namespace std;

void RunGame()
{
    string name;
    int Choice;
    Board* board = nullptr;
    Player* players[2];

    cout << "Welcome to Tic Tac Toe Games :)\n\n"
        << "What's your name: ";
    cin >> name;
    players[0] = new Player(name, 'X', 1);

    cout << "\nGames list:\n"
        << "1) X-O\n"
        << "2) Pyramic Tic Tac Toe\n"
        << "3) Connect 4 \n"
        << "4) 5x5 Tic Tac Toe\n\n"
        << "Enter the number of choice >>  ";
    cin >> Choice;

    if (Choice == 1)
        board = new XO_Board();
    else if (Choice == 2)
        board = new Pyramic_Board();
    else if (Choice == 3)
        board = new Connect4_Board();
    else if (Choice == 4)
        board = new FiveFive_Board();

    cout << "\nPlay with: \n"
        << "1) Friend\n"
        << "2) AI (Supported XO & Pyramic only)\n\n"
        << "Enter the number of choice >>  ";
    cin >> Choice;
    if (Choice == 1)
    {
        cout << "\nWhat's your name: ";
        cin >> name;
        players[1] = new Player(name, 'O', 2);
    }
    else if (Choice == 2)
    {
        players[1] = new AI_Player(board, 'O', 2);
    }


    Game_Manager* Engine = new Game_Manager(board, players);
    Engine->run();
}

int main()
{
    RunGame();
    
    return 0;
}