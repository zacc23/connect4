#include <iostream>
#include <stdlib.h>
#include <string.h>
using namespace std;

#define BOARD_X		7
#define BOARD_Y		6
#define CONNECT		4
#define PLAYERS		2

class Connect4 {
	public:

	int empty, discs, col, players;
	int slot[PLAYERS][BOARD_X][BOARD_Y];
	bool win, full;
	char disc[PLAYERS];
	string name[PLAYERS];
	
	Connect4();
	void PrintBoard();
	void DropDisc(int);
	void CheckConnect(int);
};

Connect4::Connect4() {
	discs = 0;
	empty = 0;
	players = PLAYERS;
	win = false;
        full = false;
	for (int y = BOARD_Y; y >= 0; y--)
        {
                for (int x = 0; x < BOARD_X; x++)
                {
			for (int p = 0; p < PLAYERS; p++)
			{
				slot[p][x][y] = 0;
			}
		}
	}
	for (int p = 0; p < PLAYERS; p++) 
	{
		int i;

		cout << "Enter the name of player " << p + 1 << ": ";
		cin >> name[p];
		i = 1;
                while (p - i >= 0 && name[p] == name[p - i])
                {
                                cout << "Enter a unique name: "; 
                                cin >> name[p];
                }

		cout << "Enter your disc character (ex. X/O) ";
		cin >> disc[p];
		i = 1;	
		while (p - i >= 0 && disc[p] == disc[p - i])
		{
				cout << "Enter a unique disc (ex. X/O) ";	
				cin >> disc[p];
		}
		cout << endl;
	}
}

void Connect4::PrintBoard() { // print board from top to bottom
	for (int x = 0; x < BOARD_X + 2; x++) { // print top layer
		cout << "_";
	}
	cout << endl;

	for (int y = BOARD_Y - 1; y >= 0; y--) 
	{
		cout << "|";
		for (int x = 0; x < BOARD_X; x++) 
		{
			for (int p = 0; p < PLAYERS; p++)
			{
				if (slot[p][x][y] == 1)
                                        cout << disc[p];
				else empty++;
			}	
			// place empty tile if not taken
			if (empty == PLAYERS)
				cout << "_";
			empty = 0;
		}
		cout << "|" << endl;
	}
}

void Connect4::DropDisc(int player) {
	choose:
	cout << "Choose a column to drop your disc (1-" << 
		BOARD_X << ") "; 
	cin >> col;
	while (col <= 0 || col > BOARD_X) {
		cin.clear(); // don't bug out when
		cin.ignore(); // typing a letter
		cout << "Choose a column to drop your disc \e[1m(1-" <<
                	BOARD_X << ")\e[0m ";
		cin >> col;
	}
	col--;

	// move upwards if slot is taken
	int y = 0;
	up:
	for (int p = 0; p < PLAYERS; p++)
	{	
		if (slot[p][col][y] == 1)
		{
			if (y == BOARD_Y - 1)
                        {	
				cout << "Choose an open column" << endl;	
			       	goto choose;
                	}
			else
			{	
				y++;
				goto up;
			}
		}
	}
	
	slot[player][col][y] = 1;	
}

void Connect4::CheckConnect(int player) {
	for (int y = BOARD_Y - 1; y >= 0; y--)
        {
		for (int x = 0; x < BOARD_X; x++)
		{
			int i;

			// horizonally
			i = 0;
			while (slot[player][x+i][y] == 1)
			{
				if (i == CONNECT - 1)
				{
					win = true;
					break;
				}
				i++;
			}

			// vertically
			i = 0;
                        while (slot[player][x][y+i] == 1)
                        {
                                if (i == CONNECT - 1)
				{
                                        win = true;
					break;
				}
				i++;
			}

			// diagonally upwards (y = x) 
			i = 0;
                        while (slot[player][x+i][y+i] == 1)
                        {
                                if (i == CONNECT - 1)
                                {
                                        win = true;
                                        break;
                                }
				i++;
                        }
			
			// TODO: prevent looking out of bounds
			// diagonally downwards (y = -x)
			i = 0;
                        while (slot[player][x+i][y-i] == 1)
                        {
                                if (i == CONNECT - 1)
                                {
                                        win = true;
                                        break;
                                }
				i++;
                        }
		
			// check for a full board
			for (int p = 0; p < PLAYERS; p++)
			{
				if (slot[p][x][y] == 1)
					discs += 1;
			}
		}
	}
	if (discs == PLAYERS * BOARD_X * BOARD_Y)
		full = true;
	discs = 0;
}
