/*
This Program: "Connect 4"
Author: Zachary Santoni
Date: 04-27-21
*/

#include <iostream>
#include "connect4.h"
using namespace std;

int main() {
	Connect4 C4;
	int turn = 1;

	while (C4.win == false)
	{
		cout << "Turn " << turn << endl;
		for (int p = 0; p < C4.players; p++) 
		{
			cout << "Player name: " << C4.name[p] << endl;
			C4.PrintBoard();
			C4.DropDisc(p);
			C4.CheckConnect(p);
			if (C4.win == true)
			{
				C4.PrintBoard();
                                cout << C4.name[p] << " is the winner!" << endl;
				break;	
				// TODO: bold winning discs
			}
			if (C4.full == true)
			{
				cout << "Board is full. Game over" << endl;	
				break;
			}
		}
		turn++;
	}

	return 0;
}			
