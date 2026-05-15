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
				while (true)
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
					}
				}
				break;
			}
			case 1:
				system("cls || clear");
				cout << "========== ABOUT GAME ==========" << endl << endl;

				cout << "BattleShip is a strategic naval war game played on a grid map between two players." << endl;
				cout << "The main goal of the game is to find and destroy all enemy ships before your opponent destroys yours." << endl << endl;

				cout << "Game Features:\n";
				cout << "- Menu controlled with arrow keys\n- Start Game and Exit options\n- Different player modes\n";
				cout << "- Smart bot system\n- Manual and automatic ship placement\n- Colored hit and miss effects\n";
				cout << "- Real-time ship status information\n\n";

				cout << "Game Modes:\n\n";
				cout << "1. Manual\n   - Player places ships manually\n   - Player attacks manually\n\n";
				cout << "2. Automatic\n   - Ships are placed automatically by the system\n   - Player attacks manually\n\n";
				cout << "3. Bot\n   - Bot places ships automatically\n   - Bot attacks automatically\n\n";

				cout << "Ship Types:\n- 4 ships with 1 cell\n- 3 ships with 2 cells\n- 2 ships with 3 cells\n\n";

				cout << "Ship Placement Rules:\n- Ships cannot touch each other\n- Minimum 1 cell distance is required\n";
				cout << "- Ships can be rotated\n  H -> Horizontal position\n  V -> Vertical position\n";
				cout << "- Rotation is blocked if ship goes outside the map\n\n";

				cout << "Battle System:\n- M = Missed shot\n- H = Ship hit but not destroyed\n";
				cout << "- A = Ship completely destroyed\n\n";

				cout << "Smart Bot AI:\nThe bot is not completely random.\nIf the bot hits a ship and the ship is not destroyed,\n";
				cout << "it searches nearby cells intelligently until the ship sinks.\n\n";

				cout << "Objective:\nDestroy all enemy ships before your opponent destroys yours.\n\n";

				cout << "Controls:\nArrow Keys -> Movement\nEnter -> Select\nF -> Choose ship\nH -> Horizontal position\n";
				cout << "V -> Vertical position\nESC -> Back/Menu\n";
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