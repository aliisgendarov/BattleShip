#define KeyUp 72
#define KeyDown 80
#define KeyRight 77
#define KeyLeft 75
#define Enter 13
#define ESC 27

#include <iostream>
#include <cassert>
#include <conio.h>
#include <thread>
#include <chrono>

using namespace std;

#include "player.h"
#include "helpers.h"


int main()
{
	cout << "Welcome BattleShip Game";
	this_thread::sleep_for(chrono::seconds(2));

	int choise = 0;

	while (true)
	{
		system("cls || clear");

		cout << "BattleShip" << endl;
		cout << (choise == 0 ? "->>" : "") << "\033[32mStart Game" << "\033[0m" << (choise == 0 ? "<<-" : "") << endl;
		cout << (choise == 1 ? "->>" : "") << "\033[34mAbout Game" << "\033[0m" << (choise == 1 ? "<<-" : "") << endl;
		cout << (choise == 2 ? "->>" : "") << "\033[31mExit" << "\033[0m" << (choise == 2 ? "<<-" : "") << endl;

		int c = _getch();
		keyUpAndDownMove(c, choise, 2);
		switch (c)
		{
		case Enter:
			switch (choise)
			{
			case 0:
			{
				Player p1;
				Player p2;

				int cho = 0;
				bool isRunning = true;
				
				while (isRunning)
				{
					system("cls || clear");
					cout << "Select players:" << endl;

					cout << (cho == 0 ? "->>" : "") << "Player 1: "; p1.showPlayer();
					cout << "\033[0m" << (cho == 0 ? " <<-" : "") << endl;
					cout << (cho == 1 ? "->>" : "") << "Player 2: "; p2.showPlayer();
					cout << "\033[0m" << (cho == 1 ? " <<-" : "") << endl;
					cout << (cho == 2 ? "->>" : "") << "Done" << (cho == 2 ? " <<-" : "") << endl;
					cout << (cho == 3 ? "->>" : "") << "Back Menu" << (cho == 3 ? "<<-" : "") << endl;

					int cc = _getch();
					keyUpAndDownMove(cc, cho, 3);
					switch (cc)
					{
					case KeyRight:
						if (cho == 0) p1.changeForRight();
						else if (cho == 1) p2.changeForRight();
						break;
					case KeyLeft:
						if (cho == 0) p1.changeForLeft();
						else if (cho == 1) p2.changeForLeft();
						break;
					case ESC:
						isRunning = false;
						break;
					}
				}
				break;
			}
			case 1:
				system("cls || clear");
				cout << "========== ABOUT GAME ==========" << endl << endl;

				cout << "BattleShip is a strategic naval battle game played between two players." << endl;
				cout << "The objective is to destroy all enemy ships before your opponent destroys yours.\n\n";

				cout << "Features:\n- Manual and automatic ship placement\n- Player vs Player and Bot modes\n";
				cout << "- Smart bot AI system\n- Colored hit and miss effects\n- Real-time ship status information\n\n";

				cout << "Ship Rules:\n- Ships cannot touch each other\n- Ships can be placed horizontally or vertically\n";
				cout << "- Rotation is blocked outside the map\n\n";

				cout << "Battle Symbols:\nM = Miss\nH = Hit\nA = Destroyed ship\n\n";

				cout << "Controls:\nArrow Keys -> Move\nEnter -> Select\nF -> Choose ship\nH/V -> Rotate ship\nESC -> Back/Menu\n";
				break;
			case 2:
				system("cls || clear");
				cout << "Game over!" << endl;
				return 0;
			default:
				cout << "This code is not valid!" << endl;
				break;
			}
			cout << "\nPress any key to countinue...";
			int a = _getch();
		}
	}
	return 0;
}